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


class Door {
    private:
        Lock m_lock;
        DoorSwitch m_doorSwitch;
        DoorBell m_doorBell;
        MotionSensor m_motionSensor;

    public:
        Door(Lock lock, DoorSwitch doorSwitch, DoorBell doorBell, MotionSensor motionSensor);

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

        Door *getDoor();
};

extern Door *door;
void sendTestMessage();

#endif // DOOR_H_

    
