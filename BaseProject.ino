/*
 Name:		BaseProject.ino
 Created:	3/26/2022 12:17:55 PM
 Author:	Kitecraft
*/

#include <esp_now.h>
#include "src/CC_Config.h"
#include "src/Network/Network.h"
#include "src/Network/CCWebServer.h"
#include "src/Network/OTAManager.h"
#include "src/ESPNow/EspNowManager.h"
#include "src/ESPNow/EspNowIncomingMessageQueue.h"

WiFiClient g_wifiClient;
TaskHandle_t g_webServerHandler = nullptr;
TaskHandle_t g_OTAHandler = nullptr;

EspNowIncomingMessageQueue g_espNowMessageQueue;


bool setupComplete = true;
void setup() {
    Serial.begin(115200);

    Serial.println("Beginning network connection");
    if (!connectToNetwork())
    {
        Serial.println("Failed to connect to network.  Start local webserver");
        setupComplete = false;
        xTaskCreatePinnedToCore(handleLocalWebSever, "WebServer Loop", STACK_SIZE, nullptr, WEB_SERVER_PRIORITY, &g_webServerHandler, WEBSERVER_CORE);
        //display error here
    }
    else {
        Serial.println("Connected to network succesfully.  Starting webserver.");
        xTaskCreatePinnedToCore(handleWebSever, "WebServer Loop", STACK_SIZE, nullptr, WEB_SERVER_PRIORITY, &g_webServerHandler, WEBSERVER_CORE);
        Serial.println("Started webserver handler.  Starting OTA Handler");

        xTaskCreatePinnedToCore(handleOTA, "OTA Loop", STACK_SIZE, nullptr, OTA_PRIORITY, &g_OTAHandler, OTA_CORE);
        Serial.println("Started OTA handler");
    }

    Serial.println("Beginning EspNow connection");
    if (!InitEspNow())
    {
        Serial.println("Failed to setup EspNow.  As such, I will now refuse to continue.");
        while (true) {}
    }


    Serial.println("\n\n---\nStarting");
}


void loop() {
    HandleEspNowData();

}

void HandleEspNowData()
{
    if (!g_espNowMessageQueue.IsQueueEmpty())
    {
        EspNowMessage message = g_espNowMessageQueue.GetNextItem();
        switch (message.command) {
        case CC_ACK_COMMAND:
            Serial.println("Acked");
            break;
        case CC_GET_DISTANCE:
            Serial.printf("Distance: '%i'", message.value);
            break;
        default:
            break;
        };
    }
}
