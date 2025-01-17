#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <thread>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/log/trivial.hpp>
#include "OrderBook.h"
#include <shared_mutex>

class Server {
public:
    bool SetupConnections();
    void AcceptConnections(OrderBook orderBook);
    // Shut down the server and join all threads
    void Shutdown();
private:
    std::shared_mutex order_book_mutex_; 
    int server_file_descriptor_;
    // No max size
    std::vector<int> client_file_descriptors_;
    std::vector<boost::thread> client_threads_;
    void HandleClientConnection(int client_file_descriptor, OrderBook orderBook);
    void JoinThreads();
};

#endif // SERVER_H
