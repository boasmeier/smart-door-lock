/*
 * Door.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef DOOR_H_
#define DOOR_H_

#include "Lock.hpp"
#include "DoorBell.hpp"
#include "DoorSwitch.hpp"
#include "MotionSensor.hpp"
#include "../card_reader/CardReader.hpp"


class Door {
    private:
        Lock m_lock;
        DoorSwitch m_doorSwitch;
        DoorBell m_doorBell;
        MotionSensor m_motionSensor;
        CardReader m_cardReader;

    public:
        Door(Lock& lock, DoorSwitch& doorSwitch, DoorBell& doorBell, MotionSensor& motionSensor, CardReader& cardReader);

        DoorLockState getLockState();
        void toggleLock();
        void unlock();
        void lock();

        DoorSwitchState getDoorSwitchState();
        void handleDoorSwitchOpenedEvent();
        void handleDoorSwitchClosedEvent();

        DoorBellState getDoorBellState();
        void handleDoorBellRingEvent();

        MotionState getMotionState();
        void handleMotionDetectionEvent();

        void read();

        Door *getDoor();
};

extern Door *door;

#endif // DOOR_H_

    
