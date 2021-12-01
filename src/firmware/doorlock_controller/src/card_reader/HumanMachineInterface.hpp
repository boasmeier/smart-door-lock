#ifndef HUMAN_MACHINE_INTERFACE_H
#define HUMAN_MACHINE_INTERFACE_H

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

#endif 