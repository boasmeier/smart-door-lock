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
#include "../config/DoorlockConfig.h"

class HumanMachineInterface {
    public:
        HumanMachineInterface(Led& successLed, Led& failureLed);
        void success();
        void failure();
        void blink_blocking(int n);
        void blink();
        void off();
        void on();

    private:
        Led m_successLed;
        Led m_failureLed;
        int m_blinkFreq = HMI_BLINK_FREQUENCY;  // hz
};

extern HumanMachineInterface *cardReaderHmi;

void ledOffCallback();
void ledOnCallback();
void ledToggleCallback();
void ledBlinkStopCallback();

extern Timer *ledTimer;
extern Timer *blinkTimer;
extern Timer *stopTimer;

#endif // HUMAN_MACHINE_INTERFACE_H_