#pragma once
#include <Arduino.h>
#include "Message.h"

/*-----------------------------------------------------------------------
-- IMessageQueue
-----------------------------------------------------------------------*/
template<typename T>
class IMessageQueue {
    public:
        virtual bool send(const T& message, TickType_t timeout) = 0;
        virtual bool receive(T& message, TickType_t timeout) = 0;
};


/*-----------------------------------------------------------------------
-- MessageQueueTemplate
-----------------------------------------------------------------------*/
template<typename T>
class MessageQueueTemplate : public IMessageQueue<T> {
    public:
        MessageQueueTemplate(size_t queueSize);
        bool send(const T& message, TickType_t timeout) override;
        bool receive(T& message, TickType_t timeout) override;

    protected:
        QueueHandle_t queueHandle_;
        SemaphoreHandle_t mutex_;
};

template<typename T>
MessageQueueTemplate<T>::MessageQueueTemplate(size_t queueSize) 
    : queueHandle_(xQueueCreate(queueSize, sizeof(T))),
      mutex_(xSemaphoreCreateMutex()) 
{
    xSemaphoreGive(mutex_);
}

template<typename T>
bool MessageQueueTemplate<T>::send(const T& message, TickType_t timeout) {
    if (xSemaphoreTake(mutex_, timeout) == pdTRUE) {
        bool result = xQueueSend(queueHandle_, &message, timeout) == pdPASS;
        xSemaphoreGive(mutex_);
        return result;
    } else {
        return false;
    }
}

template<typename T>
bool MessageQueueTemplate<T>::receive(T& message, TickType_t timeout) {
    if (xSemaphoreTake(mutex_, timeout) == pdTRUE) {
        bool result = xQueueReceive(queueHandle_, &message, timeout) == pdPASS;
        xSemaphoreGive(mutex_);
        return result;
    } else {
        return false;
    }
}





