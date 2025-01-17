#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "logging.h"
#include "OrderBook.h"
#include "constants.h"

#ifndef CLIENT_h
#define CLIENT_h

class Client
{
private:
    const char* ip_address_;
    int socket_;
public:
    Client() {
        ip_address_ = "127.0.0.1";
    };
    bool SetupConnections();
    bool CreateConnections();
    void send_order(std::string_view ticker, bool is_bid, long quantity, double price);
};

#endif 