#include "Client.h"


bool Client::SetupConnections() {
    struct sockaddr_in server_address;

    // Create socket file descriptor
    if ((socket_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        BOOST_LOG_TRIVIAL(error) << "Socket creation error";
        return false;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, ip_address_, &server_address.sin_addr) <= 0) {
        BOOST_LOG_TRIVIAL(error) << "Invalid address or address not supported " << ip_address_;
        return false;
    }

    // Connect to the server
    if (connect(socket_, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address)) < 0) {
        BOOST_LOG_TRIVIAL(error) << "Connection failed";
        return false;
    }

    BOOST_LOG_TRIVIAL(info) << "Connection established with server";
    return true;
};

bool Client::CreateConnections(const int quantity, const int number_of_ticks) {
    // Communication loop
    std::string message = "0";
    char buffer[BUFFER_SIZE] = {0};
    OrderBook orderBook = OrderBook("ABC ");
    // Marker for knowing first time
    bool sent_first_order = false;
    while (true) {
        // Read the server's response
        std::fill(buffer, buffer + BUFFER_SIZE, 0);
        int bytes_read = read(socket_, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            BOOST_LOG_TRIVIAL(error) << "Server disconnected";
            break;
        }
        orderBook.ParseOrderBookData(std::string(buffer, bytes_read));
        orderBook.DetermineOrders();

        if (sent_first_order) {
            // Clear order beforee sending first order
            send_order(orderBook.GetTicker(),
                        false,
                        quantity,
                        0
            );
            send_order(orderBook.GetTicker(),
                        true,
                        quantity,
                        0
            );
        }
        if (orderBook.GetBestAsk() > 0) {
            // Ask order
            send_order(orderBook.GetTicker(),
                        false,
                        quantity,
                        orderBook.GetBestAsk()
            );
            sent_first_order = true;
        }
        if (orderBook.GetBestBid() > 0) {
            // Bid order
            send_order(orderBook.GetTicker(),
                        true,
                        quantity,
                        orderBook.GetBestBid()
            );
            sent_first_order = true;
        }
        // Send the message to the server as send order is the real function
        send(socket_, message.c_str(), message.length(), MSG_DONTWAIT);
    }

    // Close the socket
    close(socket_);
    return true;
}