#pragma once
#include <Arduino.h>
#include <WebServer.h>
#include "../Utilities/IceFS.h"


static void RunWebServer()
{
    WiFi.softAPdisconnect(true);

    WebServer server(80);
    server.on("/", [&]() {
        String htmlText = IceFS_ReadFile("/web/index.html");
        htmlText.replace("%{__DEVICE_NAME__}%", __DEVICE_NAME__);
        htmlText.replace("%{ERRORTEXT}%", "");
        htmlText.replace("%{NETWORKNAME}%", GetSsid());
        htmlText.replace("%{MQTTIPADDRESS}%", GetMqttBrokerAddress());
        server.send(200, "text/html", htmlText);
        });
    server.on("/MakeItWifi", [&]() {
        String htmlText = IceFS_ReadFile("/web/index.html");
        htmlText.replace("%{__DEVICE_NAME__}%", __DEVICE_NAME__);
        if (server.arg("password") != server.arg("passwordConfirm"))
        {
            htmlText.replace("%{ERRORTEXT}%", "Passwords did not match.<br>Changes not saved.");
        }
        else {
            SetSsid(server.arg("networkName"));
            SetSsidPassword(server.arg("password"));
            SetMqttBrokerAddress(server.arg("mqttIpAddress"));
            htmlText.replace("%{ERRORTEXT}%", "Changes have been saved.");
        }
        htmlText.replace("%{NETWORKNAME}%", GetSsid());
        htmlText.replace("%{MQTTIPADDRESS}%", GetMqttBrokerAddress());
        server.send(200, "text/html", htmlText);
        });
    server.on("/reboot", [&]() {
        ESP.restart();
        });
    server.begin();
    while (true)
    {
        server.handleClient();
        delay(1);
    }
}

static void IRAM_ATTR handleWebSever(void*)
{
    RunWebServer();
}

void IRAM_ATTR handleLocalWebSever(void*)
{
    Serial.println("Local network: " + String(__DEVICE_NAME__) + " - 192.168.4.1");
    Serial.println("Starting local network...");
    IPAddress IP = WiFi.softAP(__DEVICE_NAME__);
    RunWebServer();
}