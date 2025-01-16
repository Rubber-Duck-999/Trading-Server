#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "logging.h"
#include "OrderBook.h"

#define PORT 8080
#define BUFFER_SIZE 1024


class Server {
public:
    bool SetupConnections();
    bool AcceptConnections(OrderBook orderBook);

private:
    int server_file_descriptor_;
    int client_file_descriptor_;
    void HandleClientConnection(OrderBook orderBook);
};

#endif // SERVER_H
