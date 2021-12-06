/*
 * Led.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include "Led.hpp"

Led::Led(int pin, String color) : m_pin(pin), m_color(color) {
    pinMode(m_pin, OUTPUT);
}

void Led::on() {
    digitalWrite(m_pin, HIGH);
}

void Led::off() {
    digitalWrite(m_pin, LOW);
}

void Led::toggle() {
    if(digitalRead(m_pin)) {
        digitalWrite(m_pin, LOW);
    }
    else {
        digitalWrite(m_pin, HIGH);
    }
}