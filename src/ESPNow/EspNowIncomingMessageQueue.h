#pragma once
#include <Arduino.h>
#include <ArduinoQueue.h>
#include "EspNowMessage.h"

class EspNowIncomingMessageQueue
{
private:
	ArduinoQueue<EspNowMessage> messageQueue;
	portMUX_TYPE commandQueueMutex;

public:
	EspNowIncomingMessageQueue();
	void AddItemToQueue(EspNowMessage message);
	bool IsQueueEmpty();
	EspNowMessage GetNextItem();
};

