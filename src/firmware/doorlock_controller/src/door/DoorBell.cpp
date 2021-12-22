/*
 * DoorBell.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include "SPI.h"
#include "DoorBell.hpp"
#include "../connection/PahoMqttClient.hpp"
#include "../connection/MqttTopics.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"


DoorBell::DoorBell(int pin) : m_pin(pin) {
    pinMode(DOORBELL_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(DOORBELL_PIN), ringEventISR, FALLING);
}

DoorBellState DoorBell::getState() {
    int state = digitalRead(m_pin);
    SERIAL_INFO("Read door bell state - state is %i", state);
    return state ? DoorBellState::PRESSED : DoorBellState::NOT_PRESSED;
}

void DoorBell::handleRingEvent() {
    if(doorbellEventCount > 0) {
        doorbellEventCount--;
        SERIAL_INFO("Ring event");
        MQTT_INFO(mqtt, "Ring event");
        mqtt->publish(MqttTopics::RING_EVENT, "");
        SERIAL_INFO("Door bell event count: %d", doorbellEventCount);
    }
    //SERIAL_INFO("Door bell event count: %d", doorbellEventCount);
}

static volatile unsigned long previousTime = 0;
static volatile unsigned long enterTime = 0;
void ringEventISR() {
    enterTime = millis();
    if(enterTime-previousTime > 200) {
        doorbellEventCount++;
        previousTime = enterTime;
    }
}





