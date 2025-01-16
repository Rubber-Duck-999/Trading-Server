#include "server.h"

bool Server::SetupConnections() {
    // Setup initial variables for assigning address
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    BOOST_LOG_TRIVIAL(info) << "Starting TCP Server";

    // Create socket file descriptor
    if ((server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        BOOST_LOG_TRIVIAL(error) << "TCP Socket failed";
        return false;
    }

    // Forcefully attach socket to the port
    if (setsockopt(server_file_descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        BOOST_LOG_TRIVIAL(error) << "Socket did not attach";
        close(server_file_descriptor);
        return false;
    }

    // Set up the address structure
    address.sin_family = AF_INET;
    // Binding to any adress bcause Im inside a container and this is a demo
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_file_descriptor, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
        BOOST_LOG_TRIVIAL(error) << "Bind failed on the port";
        close(server_file_descriptor);
        return false;
    }

    // Start listening for connections
    if (listen(server_file_descriptor, 3) < 0) {
        BOOST_LOG_TRIVIAL(error) << "Listen failed, recieved -1";
        close(server_file_descriptor);
        return false;
    }

    BOOST_LOG_TRIVIAL(info) << "Server is listening on port " << PORT;

    // Accept an incoming connection
    client_file_descriptor = accept(server_file_descriptor, reinterpret_cast<struct sockaddr*>(&address), reinterpret_cast<socklen_t*>(&addrlen));
    if (client_file_descriptor < 0) {
        BOOST_LOG_TRIVIAL(error) << "Accept incoming connection failed, recieved -1";
    }

    BOOST_LOG_TRIVIAL(info) << "Connection established with client";
    return true;
}

bool Server::AcceptConnections() {
    // Communicate with the client
    char buffer[BUFFER_SIZE] = {0};
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(client_file_descriptor, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            BOOST_LOG_TRIVIAL(info) << "Client disconnected";
            break;
        }

        BOOST_LOG_TRIVIAL(info) << "Received: " << buffer << ".";

        // Echo the message back to the client
        std::string custom_message = "Hello from the server!";
        send(client_file_descriptor,
            custom_message.c_str(),
            custom_message.length(),
            0);
    }

    // Close the sockets
    close(client_file_descriptor);
    close(server_file_descriptor);

    return true;
}