/*
 * HumanMachineInterface.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include "Led.hpp"
#include "HumanMachineInterface.hpp"

HumanMachineInterface::HumanMachineInterface(Led& successLed, Led& failureLed) :
m_successLed(successLed),
m_failureLed(failureLed) {
    blink();
}

void HumanMachineInterface::success() {
    m_successLed.on();
    m_failureLed.off();
    ledTimer->Start();  
}

void HumanMachineInterface::failure() {
    m_successLed.off();
    m_failureLed.on();
    ledTimer->Start();
}

void HumanMachineInterface::on() {
    m_successLed.on();
    m_failureLed.on();
}

void HumanMachineInterface::off() {
    m_successLed.off();
    m_failureLed.off();
}

void HumanMachineInterface::blink_blocking(int n) {
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

void HumanMachineInterface::blink() {
    on();
    blinkTimer->Start();
    stopTimer->Start();
}

void ledOffCallback() {
    cardReaderHmi->off();
}

void ledOnCallback() {
    cardReaderHmi->on();
}

volatile bool isOn = false;
void ledToggleCallback() {
    if(isOn) {
        cardReaderHmi->off();
        isOn = false;
    } else {
        cardReaderHmi->on();
        isOn = true;
    }
}

void ledBlinkStopCallback() {
    blinkTimer->Stop();
}
