#include "SPI.h"
#include "DoorBell.hpp"
#include "../connection/MyMqttClient.hpp"
#include "../connection/MqttTopics.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"

DoorBell::DoorBell(int pin) : m_pin(pin) {
    pinMode(m_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(m_pin), handleRingEvent, FALLING);
}

DoorBellState DoorBell::getState() {
    int state = digitalRead(m_pin);
    SERIAL_INFO("Read door bell state %i", state);
    return  state ? DoorBellState::PRESSED : DoorBellState::NOT_PRESSED;
}

void handleRingEvent() {
    SERIAL_INFO("Ring event");
    MQTT_INFO(mqtt, "Ring event");
    mqtt->publish(MqttTopics::RING_EVENT, "");
}