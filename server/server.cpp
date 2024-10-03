#include "server.h"


Server::Server(int port){
    if (port > 9999 || port < 0) {
        error("error 204", "is port bad");
    }

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("error 5", "WSAStartup is bad");
    }

    sock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_ == INVALID_SOCKET) {
        error("error 4", "invalid socket");
    }

    port_ = port;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        error("error 1", "is bad addr or port");
    }

    if (listen(sock_, 5) == SOCKET_ERROR) {
        error("error 2", "is bad listen socket");
    }
}


void Server::startServer() {
    clilen = sizeof(cliaddr);
    while (true) {
        if (IsDebuggerPresent()) {
            error("error 543", "debbager detect!");
        }

        if (accept(sock_, (struct sockaddr*)&cliaddr, &clilen) < 0) {
            errorNotStop("error 201", "listen packet is bad");
            continue;
        }

        size_t bytes_received = recv(sock_, buffer, sizeof(buffer), 0);

        if (bytes_received < 0) {
            continue;
        }

        const std::string jsonString(buffer, buffer + sizeof(buffer));
        
        processingRequests Processing(jsonString);
        Processing.transmissionRequests();
    }
}


void Server::stopServer() {
    closesocket(sock_);
}


Server::~Server() {
    closesocket(sock_);
    WSACleanup();
}


void error(std::string head, std::string body) {
    std::cout << std::format("{}: {}", head, body);
    exit(1);
}


void errorNotStop(std::string head, std::string body) {
    std::cout << std::format("{}: {}", head, body);
}