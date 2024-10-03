#ifndef HEADERS_H
#define HEADERS_H


#pragma once

#include "../attack/attack.h"
#include <string>
#include <iostream>
#include <format>
#include <nlohmann/json.hpp>



class processingRequests {
private:
    std::string jsonString;
public:
    processingRequests(std::string jsonString);
    void transmissionRequests();
};

#endif