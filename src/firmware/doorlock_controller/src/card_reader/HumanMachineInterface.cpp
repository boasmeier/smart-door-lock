#include "Led.hpp"
#include "HumanMachineInterface.hpp"

HumanMachineInterface::HumanMachineInterface(Led successLed, Led failureLed) :
m_successLed(successLed),
m_failureLed(failureLed) {
    blink(3);
}

void HumanMachineInterface::success() {
    m_successLed.on();
    m_failureLed.off();
    delay(300);
    m_successLed.off();
    m_failureLed.off();    
}

void HumanMachineInterface::failure() {
    m_successLed.off();
    m_failureLed.on();
    delay(300);
    m_successLed.off();
    m_failureLed.off();
}

void HumanMachineInterface::blink(int n) {
    int ms = 1000/m_blinkFreq;
    for(int i = 0; i < n; i++) {
        m_successLed.on();
        m_failureLed.on();
        delay(ms);
        m_successLed.off();
        m_failureLed.off();
        delay(ms);
    }
}
