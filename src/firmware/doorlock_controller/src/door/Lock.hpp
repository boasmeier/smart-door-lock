#pragma once

enum class LockState { UNLOCKED, LOCKED };

class Lock {
    private:
        int m_pin;
        LockState m_state;

    public:
        Lock(int pin, LockState state);
        LockState getState();
        void toggle();
        void lock();
        void unlock();
};
    