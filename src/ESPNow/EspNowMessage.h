#pragma once
#include <Arduino.h>
#include "CandyCraneCommands.h"

typedef struct EspNowMessage {
    int command = CC_NONE;
    uint16_t value = -1;

    EspNowMessage() {}
    EspNowMessage(const EspNowMessage& orig)
    {
        command = orig.command;
        value = orig.value;
    }
} EspNowMessage;
