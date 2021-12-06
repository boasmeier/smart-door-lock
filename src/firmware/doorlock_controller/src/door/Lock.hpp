/*
 * Lock.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
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
    