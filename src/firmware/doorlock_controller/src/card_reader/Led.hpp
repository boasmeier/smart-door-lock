#pragma once

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