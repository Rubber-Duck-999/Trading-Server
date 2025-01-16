#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "logging.h"
#include "constants.h"
#include <arpa/inet.h>

#ifndef SERVER_h
#define SERVER_h

class Server
{
private:
    int server_file_descriptor, client_file_descriptor;
public:
    Server() {};
    bool SetupConnections();
    bool AcceptConnections();
};

#endif 