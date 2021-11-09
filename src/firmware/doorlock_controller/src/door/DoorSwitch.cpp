#include "SPI.h"
#include "DoorSwitch.hpp"

DoorSwitch::DoorSwitch(int pin) : m_pin(pin) {
    pinMode(m_pin, INPUT);
}

DoorSwitchState DoorSwitch::getState() {
    int state = digitalRead(m_pin);
    return  state ? DoorSwitchState::OPEN : DoorSwitchState::CLOSED;
}