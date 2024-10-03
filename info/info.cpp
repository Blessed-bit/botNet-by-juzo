#include "info.h"

InfoSystem::InfoSystem() {
    this->getHDD();
    this->getRam();
    this->getUserName();
    this->getMac();
    //this->getGPU();
    //this->getNameCPU();
}


void InfoSystem::getNameCPU() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    // update soon

}


//void InfoSystem::getGPU() {
    //nvmlDevice_t device;
    //nvmlDeviceGetHandleByIndex(0, &device);

    //char deviceName[256];
    //nvmlDeviceGetName(device, deviceName, 256);
    //this->GPU = deviceName;

//}


void InfoSystem::getHDD() {
    ULARGE_INTEGER freeBytesAvailable;
    ULARGE_INTEGER totalBytes;
    ULARGE_INTEGER totalFreeBytes;
    char mbstr[256];

    LPCWSTR numberDisk[11] = { L"A://",L"B://",L"C://",L"D://",L"E://",L"F://",L"G://",L"H://",L"I://",L"J://" };


    for (int i = 0; i <= (sizeof(numberDisk) / sizeof(double) - 1); i++) {
        if (GetDiskFreeSpaceEx(numberDisk[i], &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
            memoryHDD.push_back((double)totalBytes.QuadPart / (1024 * 1024 * 1024));
            std::wcstombs(mbstr, numberDisk[i], sizeof(mbstr));
            std::string str(mbstr);
            nameHDD.push_back(mbstr);
        }
    }
}

 
void InfoSystem::getRam() {
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&ms);
    this->RAM = std::to_string(ms.ullTotalPhys / 1024 / 1024);
}


void InfoSystem::getUserName(){
    char userNameTemp[256];
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    DWORD userNameLen = sizeof(userNameTemp);

    GetUserNameA(userNameTemp, &userNameLen);
    this->USERNAME = std::string(userNameTemp);

}


void InfoSystem::getMac() {
    ULONG outBufLen = sizeof(IP_ADAPTER_INFO);
    PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(outBufLen);

    ULONG result = GetAdaptersInfo(pAdapterInfo, &outBufLen);
    if (result != ERROR_SUCCESS) {
        error("error 342", "not found MAC");
    }

    for (PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter; pAdapter = pAdapter->Next) {
        printf("Adapter Name: %s\n", pAdapter->AdapterName);
        for (int i = 0; i < 6; i++) {
            MAC += pAdapter->Address[i];
        }
    }

    free(pAdapterInfo);
}


void InfoSystem::sendData() {
    std::string key;
    jsonData["gpuName"] = GPU;
    jsonData["userName"] = USERNAME;
    for (int i = 0; i < nameHDD.size() && i < memoryHDD.size(); i++) {
        key = "disk " + nameHDD[i];
        jsonData[key.c_str()] = memoryHDD[i];
    }
    //jsonData["cpuName"] = CPU;
    jsonData["macAddress"] = MAC;
    manage.sendInfo(jsonData);
}