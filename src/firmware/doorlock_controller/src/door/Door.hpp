#pragma once

#include "Lock.hpp"
#include "DoorSwitch.hpp"
#include "MotionSensor.hpp"


class Door {
    private:
        Lock m_lock;
        DoorSwitch m_doorSwitch;
        MotionSensor m_motionSensor;

    public:
        Door(Lock lock, DoorSwitch doorSwitch, MotionSensor motionSensor);
        LockState getLockState();
        DoorSwitchState getDoorSwitchState();
        MotionState getMotionState();
};

static Door *door;
    
