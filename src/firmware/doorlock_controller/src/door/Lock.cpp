#include "SPI.h"
#include "Lock.hpp"

Lock::Lock(int pin, LockState state) : m_pin(pin), m_state(state) {
    pinMode(m_pin, OUTPUT);
}

LockState Lock::getState() {
    return m_state;
}

void Lock::toggle() {
    if(m_state == LockState::LOCKED) {
        unlock();
    } else {
        lock();
    }
}

void Lock::lock() {
    m_state = LockState::LOCKED;
    digitalWrite(m_pin, HIGH);
}

void Lock::unlock() {
    m_state = LockState::UNLOCKED;
    digitalWrite(m_pin, LOW);
}