#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <thread>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/log/trivial.hpp>
#include <mutex>
#include "OrderBook.h"

class Server {
public:
    bool SetupConnections();
    void AcceptConnections(OrderBook ordrBook);
private:
    std::mutex order_book_mutex_; 
    int server_file_descriptor_;
    // No max size
    std::vector<int> client_file_descriptors_;
    void HandleClientConnection(int client_file_descriptor, OrderBook orderBook);
};

#endif // SERVER_H
