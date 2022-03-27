#include "EspNowIncomingMessageQueue.h"

EspNowIncomingMessageQueue::EspNowIncomingMessageQueue()
{
	ArduinoQueue<EspNowMessage> messageQueue(3);
	commandQueueMutex = portMUX_INITIALIZER_UNLOCKED;
}

void EspNowIncomingMessageQueue::AddItemToQueue(EspNowMessage message)
{
	EspNowMessage qi(message);

	portENTER_CRITICAL(&commandQueueMutex);
	messageQueue.enqueue(qi);
	portEXIT_CRITICAL(&commandQueueMutex);
}

bool EspNowIncomingMessageQueue::IsQueueEmpty()
{
	return messageQueue.isEmpty();
}

EspNowMessage EspNowIncomingMessageQueue::GetNextItem()
{
	EspNowMessage ret;

	portENTER_CRITICAL(&commandQueueMutex);
	ret = messageQueue.dequeue();
	portEXIT_CRITICAL(&commandQueueMutex);

	return ret;
}