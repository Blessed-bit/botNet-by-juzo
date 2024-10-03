#ifndef SERVER_H
#define SERVER_H


#pragma once

#include "../attack/attack.h"
#include <string>
#include <iostream>
#include <format>
#include "headersProcessing.h"
#include <nlohmann/json.hpp>


#pragma comment(lib, "ws2_32.lib")


class Server {
private:
    SOCKET sock_;
    struct sockaddr_in servaddr, cliaddr;
    int connfd, clilen, port_;
    char buffer[1024];

public:
    Server(int port);
    ~Server();
    void startServer();
    void stopServer();
};


void error(std::string head, std::string body);
void errorNotStop(std::string head, std::string body);

#endif