#include <Arduino.h>

#include "MqttMessageHandler.hpp"
#include "MqttTopics.hpp"
#include "../door/Door.hpp"

void MqttMessageHandler::handleMessage(String topic, String msg) {
    if(topic == MqttTopics::UNLOCK) {
        handleUnlock();
    }
    else if(topic == MqttTopics::LOCK) {
        handleLock();
    }
}

void MqttMessageHandler::handleUnlock() {
    door->unlock();
}

void MqttMessageHandler::handleLock() {
    door->lock();
}