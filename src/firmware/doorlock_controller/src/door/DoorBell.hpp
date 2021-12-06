/*
 * DoorBell.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#pragma once
#include <Arduino.h>
enum class DoorBellState { NOT_PRESSED, PRESSED };

class DoorBell {
    private:
        int m_pin;

    public:
        DoorBell(int pin);
        DoorBellState getState();
        void handleRingEvent();
};

// use byte because the arduino uno wifi rev2 is a 8-bit mcu. Otherwise use ATOMIC_BLOCk macro to access m_eventCount
static volatile byte doorbellEventCount = 0;
void ringEventISR();