#include "client.h"

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

bool Client::CreateConnections() {
    // Communication loop
    std::string message = "This is the client";
    char buffer[BUFFER_SIZE] = {0};
    while (true) {
        // Send the message to the server
        send(socket_, message.c_str(), message.length(), 0);

        // Read the server's response
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(socket_, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            BOOST_LOG_TRIVIAL(info) << "Server disconnected";
            break;
        }

        BOOST_LOG_TRIVIAL(info) << "Server response: " << buffer << ".";
    }

    // Close the socket
    close(socket_);
    return true;
}
