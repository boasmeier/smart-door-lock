/*
 * HumanMachineInterface.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef HUMAN_MACHINE_INTERFACE_H_
#define HUMAN_MACHINE_INTERFACE_H_

#include "Led.hpp"
#include "../lib/timer/Timer.h"

class HumanMachineInterface {
    public:
        HumanMachineInterface(Led successLed, Led failureLed);
        void success();
        void failure();
        void blink(int n);
        void off();
        void on();

    private:
        Led m_successLed;
        Led m_failureLed;
        int m_blinkFreq = 2;  // hz
};

void ledOffCallback();

extern HumanMachineInterface *cardReaderHmi;
extern Timer *ledTimer;

#endif // HUMAN_MACHINE_INTERFACE_H_