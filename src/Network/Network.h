#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "../CC_Config.h"
#include "../Utilities/PreferencesManager.h"

extern WiFiClient g_wifiClient;

static bool connectToNetwork()
{
    WiFi.hostname(__DEVICE_NAME__);
    WiFi.mode(WIFI_STA);
    if (GetSsid().equals(""))
    {
        return false;
    }

    int tryCount = 1;
    bool connected = false;
    while (tryCount <= NETWORK_TRY_TIMES) {
        Serial.printf("Try #%i to connect to network '%s'\n", tryCount, GetSsid());
        WiFi.disconnect();
        WiFi.begin(GetSsid().c_str(), GetSsidPassword().c_str());
        int waitCount = 0;
        while (waitCount < NETWORK_WAIT_TIME_PER_TRY * 2) {
            if (WiFi.status() == WL_CONNECTED) {
                Serial.print("Connected to network: " + GetSsid() + " - ");
                Serial.println(WiFi.localIP());
                return true;
            }
            delay(500);
            waitCount++;
        }
        tryCount++;
    }
    return false;
}