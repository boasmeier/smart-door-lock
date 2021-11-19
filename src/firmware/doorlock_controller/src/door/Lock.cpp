#include "SPI.h"
#include "Lock.hpp"
#include "../connection/MyMqttClient.hpp"
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
    m_state = DoorLockState::UNLOCKED;
    SERIAL_INFO("Door unlocked, state=%i", m_state);
    MQTT_INFO(mqtt, "Door unlocked");
    digitalWrite(m_pin, LOW);
}

void Lock::lock() {
    m_state = DoorLockState::LOCKED;
    SERIAL_INFO("Door locked, state=%i", m_state);
    MQTT_INFO(mqtt, "Door locked");
    digitalWrite(m_pin, HIGH);
}

