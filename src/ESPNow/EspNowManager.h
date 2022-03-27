#pragma once
#include <Arduino.h>
#include "EspNowMessage.h"
#include "EspNowIncomingMessageQueue.h"

extern EspNowIncomingMessageQueue g_espNowMessageQueue;
static uint8_t broadcastAddress[] = { 0x84, 0xCC, 0xA8, 0x83, 0xD0, 0x92 };


// callback when data is sent
static void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
    //Serial.print("\r\nLast Packet Send Status:\t");
    //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

static void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
    EspNowMessage message;
    memcpy(&message, incomingData, sizeof(message));
    g_espNowMessageQueue.AddItemToQueue(message);
}

static bool InitEspNow()
{
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return false;
    }

    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 1;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return false;
    }
    return true;
}

static bool SendEspNowCommand(CANDY_CRANE_COMMANDS command, int valueToSend = -1)
{
    EspNowMessage espNowOutgoingMessage;
    espNowOutgoingMessage.command = command;
    espNowOutgoingMessage.value = valueToSend;
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*)&espNowOutgoingMessage, sizeof(espNowOutgoingMessage));
    if (result != ESP_OK) {
        return false;
    }

    return true;
}