#include "SPI.h"
#include "DoorSwitch.hpp"
#include "Door.hpp"
#include "../connection/MyMqttClient.hpp"
#include "../connection/MqttTopics.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"

DoorSwitch::DoorSwitch(int pin) : m_pin(pin) {
    pinMode(m_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(m_pin), handleDoorOpened, FALLING);
    attachInterrupt(digitalPinToInterrupt(m_pin), handleDoorClosed, RISING);
}

DoorSwitchState DoorSwitch::getState() {
    int state = digitalRead(m_pin);
    return  state ? DoorSwitchState::CLOSED : DoorSwitchState::OPEN;
}

void handleDoorOpened() {
    if(door->getLockState() == DoorLockState::LOCKED) {
        triggerIntrusionEvent();
    }
    else {
        SERIAL_INFO("Door opened");
        MQTT_INFO(mqtt, "Door opened");
        mqtt->publish(MqttTopics::DOOR_STATE, "{ \"doorState\": \"open\" }");
    }
}

void handleDoorClosed() {
    SERIAL_INFO("Door closed");
    MQTT_INFO(mqtt, "Door closed");
    mqtt->publish(MqttTopics::DOOR_STATE, "{ \"doorState\": \"closed\" }");
}

void triggerIntrusionEvent() {
    SERIAL_INFO("INTRUSION DETECTED!");
    MQTT_INFO(mqtt, "INTRUSION DETECTED!");
    mqtt->publish(MqttTopics::INTRUSION_EVENT, "");
}

