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

Door::Door(Lock lock, DoorSwitch doorSwitch, DoorBell doorBell, MotionSensor motionSensor) :
    m_lock(lock),
    m_doorSwitch(doorSwitch),
    m_doorBell(doorBell),
    m_motionSensor(motionSensor)
{

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
}

void Door::lock() {
    m_lock.lock();
}