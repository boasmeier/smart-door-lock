#pragma once

enum class DoorLockState { UNLOCKED, LOCKED };

class Lock {
    private:
        int m_pin;
        DoorLockState m_state;

    public:
        Lock(int pin, DoorLockState state);
        DoorLockState getState();
        void toggle();
        void unlock();
        void lock();
};
    