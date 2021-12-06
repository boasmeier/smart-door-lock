/*
 * Led.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef LED_H_
#define LED_H_

#include "Arduino.h"

class Led {
    public:
        Led(int pin, String color);
        void on();
        void off();
        void toggle();

    private:
        int m_pin;
        String m_color;
};

#endif // LED_H_