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
        DoorSwitchState getDoorSwitchState();
        DoorBellState getDoorBellState();
        MotionState getMotionState();
        void toggleLock();
        void unlock();
        void lock();
};

static Door *door;
    
