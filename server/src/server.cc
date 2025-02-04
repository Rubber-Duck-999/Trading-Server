#include "Server.h"

bool Server::SetupConnections() {
    // Setup initial variables for assigning address
    struct sockaddr_in address;
    int opt = 1;

    BOOST_LOG_TRIVIAL(info) << "Starting TCP Server";

    // Create socket file descriptor
    if ((server_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        BOOST_LOG_TRIVIAL(error) << "TCP Socket failed";
        return false;
    }

    // Found issue when trying 2 clients, non blocking accept
    int flags = fcntl(server_file_descriptor_, F_GETFL, 0);
    fcntl(server_file_descriptor_, F_SETFL, flags | O_NONBLOCK);

    // Forcefully attach socket to the port
    if (setsockopt(server_file_descriptor_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        BOOST_LOG_TRIVIAL(error) << "Socket did not attach";
        close(server_file_descriptor_);
        return false;
    }

    // Set up the address structure
    address.sin_family = AF_INET;
    // Binding to any adress bcause Im inside a container and this is a demo
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_file_descriptor_, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
        BOOST_LOG_TRIVIAL(error) << "Bind failed on the port";
        close(server_file_descriptor_);
        return false;
    }

    // Start listening for connections
    if (listen(server_file_descriptor_, 4) < 0) {
        BOOST_LOG_TRIVIAL(error) << "Listen failed, recieved -1";
        close(server_file_descriptor_);
        return false;
    }

    BOOST_LOG_TRIVIAL(info) << "Server is listening on port " << PORT;

    return true;
}

void Server::AcceptConnections(OrderBook orderBook) {
    BOOST_LOG_TRIVIAL(info) << "Wait for incoming client connections";
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    while (true) {
        // Accept an incoming connection
        int client_file_descriptor = accept(server_file_descriptor_, reinterpret_cast<struct sockaddr*>(&address), reinterpret_cast<socklen_t*>(&addrlen));
        if (client_file_descriptor < 0) {
            // If no client is available, continue accepting
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                continue;
            } else {
                BOOST_LOG_TRIVIAL(error) << "Accept incoming connection failed: " << strerror(errno);
                continue;
            }
        }

        BOOST_LOG_TRIVIAL(info) << "Connection established with client";

        client_file_descriptors_.push_back(client_file_descriptor);

        // Create a thread for handling the client connection
        try {
            BOOST_LOG_TRIVIAL(info) << "Creating client thread";
            boost::thread client_thread(&Server::HandleClientConnection, this, client_file_descriptor, orderBook);
            client_threads_.push_back(std::move(client_thread));
        } catch (const std::exception& e) {
            BOOST_LOG_TRIVIAL(error) << "Error in thread creation: " << e.what();
        }
    }
}

void Server::HandleClientConnection(int client_file_descriptor, OrderBook orderBook) {
    try {
        // Communicate with the client
        BOOST_LOG_TRIVIAL(info) << "Start message session " << client_file_descriptor;
        while (true) {
            // Send a response back to the client
            std::shared_lock<std::shared_mutex> lock(order_book_mutex_);
            std::string orderBookString = orderBook.GetOrderBookData();
            // Non blocking flag for sending
            ssize_t send_status = send(client_file_descriptor,
                orderBookString.c_str(),
                orderBookString.length(),
                MSG_DONTWAIT);
            if (send_status == -1) {
                BOOST_LOG_TRIVIAL(error) << "Local error in sending detected";
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // Close the client connection
        close(client_file_descriptor);
    } catch (const std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << "Error in thread handling: " << e.what();
    }
}

void Server::Shutdown() {
    BOOST_LOG_TRIVIAL(info) << "Shutting down tcp server";

    // Join all threads during shutdown
    for (auto& thread : client_threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    for (int client_file_descriptor : client_file_descriptors_) {
        close(client_file_descriptor);
    }

    // Close the server socket
    close(server_file_descriptor_);
}