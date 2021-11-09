#include "SPI.h"
#include "MotionSensor.hpp"

MotionSensor::MotionSensor(int pin) : m_pin(pin) {
    pinMode(m_pin, INPUT_PULLUP);
}

MotionState MotionSensor::getState() {
    int state = digitalRead(m_pin);
    return state ? MotionState::ACTIVITY : MotionState::NO_ACTIVITY;
}