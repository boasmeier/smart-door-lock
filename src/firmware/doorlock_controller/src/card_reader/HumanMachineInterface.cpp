#include "Led.hpp"
#include "HumanMachineInterface.hpp"

HumanMachineInterface::HumanMachineInterface(Led successLed, Led failureLed) :
m_successLed(successLed),
m_failureLed(failureLed) {
    blink(2);
}

void HumanMachineInterface::success() {
    m_successLed.on();
    m_failureLed.off();
}

void HumanMachineInterface::failure() {
    m_successLed.off();
    m_failureLed.on();
}

void HumanMachineInterface::blink(int n) {
    int ms = (1/m_blinkFreq)*1000;
    for(int i = 0; i < n; i++) {
        m_successLed.on();
        m_failureLed.on();
        delay(ms);
        m_successLed.off();
        m_failureLed.off();
        delay(ms);
    }
}
