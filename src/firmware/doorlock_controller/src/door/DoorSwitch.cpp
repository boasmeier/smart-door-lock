/*
 * DoorSwitch.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include "SPI.h"
#include "DoorSwitch.hpp"
#include "Door.hpp"
#include "../connection/PahoMqttClient.hpp"
#include "../connection/MqttTopics.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"

DoorSwitch::DoorSwitch(int pinOpen, int pinClose) : m_pinOpen(pinOpen), m_pinClose(pinClose) {
    pinMode(m_pinOpen, INPUT);
    pinMode(m_pinClose, INPUT);
    // use two different pins with two different interrupts because interrupts on both edges of same pin doesn't
    // work reliable
    attachInterrupt(digitalPinToInterrupt(m_pinOpen), doorSwitchOpenedISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(m_pinClose), doorSwitchClosedISR, RISING);
}

DoorSwitchState DoorSwitch::getState() {
    int state = digitalRead(m_pinOpen);
    SERIAL_INFO("Read door switch state - state is %i", state);
    return state ? DoorSwitchState::CLOSED : DoorSwitchState::OPEN;
}

static volatile unsigned long previousTime = 0;
static volatile unsigned long enterTime = 0;

void doorSwitchOpenedISR() {
    enterTime = millis();
    if(enterTime-previousTime > 200) {
        doorOpenendEventCount++;
        previousTime = enterTime;
    }
}

void doorSwitchClosedISR() {
    //SERIAL_INFO("previous: %d, enter: %d", previousTime, enterTime);
    enterTime = millis();
    if(enterTime-previousTime > 200) {
        doorClosedEventCount++;
        previousTime = enterTime;
    }
}

void DoorSwitch::handleDoorOpenedEvent() {
    if(doorOpenendEventCount>0){
        doorOpenendEventCount--;
        if(door->getLockState() == DoorLockState::LOCKED) {
            triggerIntrusionEvent();
        }
        else {
            SERIAL_INFO("Door opened");
            MQTT_INFO(mqtt, "Door opened");
            mqtt->publish(MqttTopics::DOOR_STATE, "{ \"doorState\": \"open\" }");
        }
        SERIAL_INFO("Door switch opened event count: %d", doorOpenendEventCount);
    }
    //SERIAL_INFO("Door switch opened event count: %d", doorOpenendEventCount);
}

void DoorSwitch::handleDoorClosedEvent() {
    if(doorClosedEventCount>0) {
        doorClosedEventCount--;
        SERIAL_INFO("Door closed");
        MQTT_INFO(mqtt, "Door closed");
        mqtt->publish(MqttTopics::DOOR_STATE, "{ \"doorState\": \"closed\" }");
        SERIAL_INFO("Door switch closed event count: %d", doorClosedEventCount);
    }
    //SERIAL_INFO("Door switch closed event count: %d", doorClosedEventCount);
}



void triggerIntrusionEvent() {
    SERIAL_INFO("INTRUSION DETECTED!");
    MQTT_INFO(mqtt, "INTRUSION DETECTED!");
    mqtt->publish(MqttTopics::INTRUSION_EVENT, "");
}

