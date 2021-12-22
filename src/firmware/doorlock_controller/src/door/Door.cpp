/*
 * Door.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include "Door.hpp"
#include "Lock.hpp"
#include "DoorSwitch.hpp"
#include "DoorBell.hpp"
#include "MotionSensor.hpp"
#include "../card_reader/CardReader.hpp"
#include "../connection/MqttTopics.hpp"
#include "../connection/PahoMqttClient.hpp"
#include "../logger/MqttLogger.hpp"
#include "../logger/SerialLogger.hpp"

Door::Door(Lock& lock, DoorSwitch& doorSwitch, DoorBell& doorBell, MotionSensor& motionSensor, CardReader& cardReader, UidEepromStore& uidStore):
    m_lock(lock),
    m_doorSwitch(doorSwitch),
    m_doorBell(doorBell),
    m_motionSensor(motionSensor),
    m_cardReader(cardReader),
    m_uidStore(uidStore)
{

}

void Door::read() {
    String uid = m_cardReader.read();
    if(uid.equals("")) {
        return;
    }
    checkCardPermission(uid);
}

void Door::checkCardPermission(String uid) {
    if(m_uidStore.contains(uid)) {
        SERIAL_INFO("Card with UID %s authorized and entry is granted", uid.c_str());
        MQTT_INFO(mqtt, "Card with UID %s authorized and entry is granted", uid.c_str());
        char msg[LOG_SIZE_MAX];
        strcpy(msg, "{ \"authorized\": \"true\", \"uid\": \"");
        strcat(msg, uid.c_str());
        strcat(msg, "\" }");
        mqtt->publish(MqttTopics::CARD_EVENT, msg);
        cardReaderHmi->success();
        this->unlock();
    }
    else {
        SERIAL_INFO("Card with UID %s not authorized", uid.c_str());
        MQTT_INFO(mqtt, "Card with UID %s not authorized", uid.c_str());
        char msg[LOG_SIZE_MAX];
        strcpy(msg, "{ \"authorized\": \"false\", \"uid\": \"");
        strcat(msg, uid.c_str());
        strcat(msg, "\" }");
        mqtt->publish(MqttTopics::CARD_EVENT, msg);
        cardReaderHmi->failure();
        this->lock();
    }
}

DoorLockState Door::getLockState() {
    return m_lock.getState();
}

DoorBellState Door::getDoorBellState() {
    return m_doorBell.getState();
}

void Door::handleDoorBellRingEvent() {
    m_doorBell.handleRingEvent();
}

DoorSwitchState Door::getDoorSwitchState() {
    return m_doorSwitch.getState();
}

void Door::handleDoorSwitchOpenedEvent() {
    m_doorSwitch.handleDoorOpenedEvent();
}

void Door::handleDoorSwitchClosedEvent() {
    m_doorSwitch.handleDoorClosedEvent();
}

MotionState Door::getMotionState() {
    return m_motionSensor.getState();
}

void Door::handleMotionDetectionEvent() {
    m_motionSensor.handleMotionDetection();
}

void Door::toggleLock() {
    m_lock.toggle();
}

void Door::unlock() {
    m_lock.unlock();
    lockTimer->Start();
}

void Door::lock() {
    m_lock.lock();
}

void lockCallback() {
    door->lock();
}