#pragma once
#include <Arduino.h>
#include <ArduinoOTA.h>
#include "../CC_Config.h"

static int g_OTA_Completion_Percentage = 0;
void IRAM_ATTR handleOTA(void*)
{
    ArduinoOTA.setHostname(__DEVICE_NAME__);
    //ArduinoOTA.setHostname("SlobsterDeck");
    ArduinoOTA
        .onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
        {
            type = "sketch";
        }
        else // U_SPIFFS
        {
            type = "filesystem";
        }
        Serial.println("\n\n---STARTING OTA FIRMWARE UPDATE---");
        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        //SPIFFS.end();
        //OTA_In_Progress = true;
        //allQueues.AddItemToDisplayQueue(DISPLAY_COMMAND_UPDATE_VALUE, DISPLAY_UPDATE_KEY_OTA_STARTING, "");
            })

        .onEnd([]() {
                Serial.println("OTA FIRMWARE UPDATE completed");
                delay(1000);
            })

                .onProgress([](unsigned int progress, unsigned int total) {
                int percentage = progress / (total / 100);
                if (percentage != g_OTA_Completion_Percentage)
                {
                    g_OTA_Completion_Percentage = percentage;
                    if (!(percentage)) {
                        Serial.println("OTA FIRMWARE UPDATE PROGRESS: " + String(percentage) + "%");
                    }

                }
                    })

                .onError([](ota_error_t error) {
                        Serial.printf("Error[%u]: ", error);
                        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
                        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
                        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
                        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
                        else if (error == OTA_END_ERROR) Serial.println("End Failed");
                    });

                    ArduinoOTA.begin();


                    while (true) {
                        ArduinoOTA.handle();
                        delay(1);
                    }
}