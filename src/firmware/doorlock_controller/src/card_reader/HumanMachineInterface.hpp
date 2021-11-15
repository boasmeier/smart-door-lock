#pragma once

#include "Led.hpp"

class HumanMachineInterface {
    public:
        HumanMachineInterface(Led successLed, Led failureLed);
        void success();
        void failure();
        void blink(int n);

    private:
        Led m_successLed;
        Led m_failureLed;
        int m_blinkFreq = 2;  // hz
};

static HumanMachineInterface *cardReaderHmi;