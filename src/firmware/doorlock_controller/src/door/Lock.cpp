/*
 * Lock.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include "SPI.h"
#include "Lock.hpp"
#include "../connection/PahoMqttClient.hpp"
#include "../connection/MqttTopics.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"

Lock::Lock(int pin, DoorLockState state) : m_pin(pin), m_state(state) {
    pinMode(m_pin, OUTPUT);
}

DoorLockState Lock::getState() {
    return m_state;
}

void Lock::toggle() {
    if(m_state == DoorLockState::LOCKED) {
        unlock();
    } else {
        lock();
    }
}

void Lock::unlock() {
    if(m_state == DoorLockState::UNLOCKED) {
        SERIAL_DEBUG("Door already unlocked");
        MQTT_DEBUG(mqtt, "Door already unlocked");
        return;
    }
    m_state = DoorLockState::UNLOCKED;
    SERIAL_INFO("Door unlocked, state=%i", m_state);
    MQTT_INFO(mqtt, "Door unlocked");
    mqtt->publish(MqttTopics::LOCK_STATE, "{ \"lockState\": \"unlocked\" }");
    digitalWrite(m_pin, HIGH);
}

void Lock::lock() {
    if(m_state == DoorLockState::LOCKED) {
        SERIAL_DEBUG("Door already locked");
        MQTT_DEBUG(mqtt, "Door already locked");
        return;
    }
    m_state = DoorLockState::LOCKED;
    SERIAL_INFO("Door locked, state=%i", m_state);
    MQTT_INFO(mqtt, "Door locked");
    mqtt->publish(MqttTopics::LOCK_STATE, "{ \"lockState\": \"locked\" }");
    digitalWrite(m_pin, LOW);
}



