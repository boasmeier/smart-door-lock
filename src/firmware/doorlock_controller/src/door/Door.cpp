#include "Door.hpp"
#include "Lock.hpp"
#include "DoorSwitch.hpp"
#include "MotionSensor.hpp"

Door::Door(Lock lock, DoorSwitch doorSwitch, MotionSensor motionSensor) :
    m_lock(lock),
    m_doorSwitch(doorSwitch),
    m_motionSensor(motionSensor) 
{

}

LockState Door::getLockState() {
    return m_lock.getState();
}

DoorSwitchState Door::getDoorSwitchState() {
    return m_doorSwitch.getState();
}

MotionState Door::getMotionState() {
    return m_motionSensor.getState();
}