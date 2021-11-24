#pragma once

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

    
