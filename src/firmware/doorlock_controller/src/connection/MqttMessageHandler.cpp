/*
 * MqttMessageHandler.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include <Arduino.h>

#include "MqttMessageHandler.hpp"
#include "MqttTopics.hpp"
#include "../door/Door.hpp"
#include "../logger/SerialLogger.hpp"

void MqttMessageHandler::handleMessage(String topic, String msg) {
    SERIAL_INFO("onMqttMessage - topic: %s - message: %s", topic.c_str(), msg.c_str());
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
