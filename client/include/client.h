#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "logging.h"
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
        ip_address_ = "server";
    };
    bool SetupConnections();
    bool CreateConnections();
};

#endif 