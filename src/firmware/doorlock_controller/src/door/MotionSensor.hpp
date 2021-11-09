#pragma once

enum class MotionState { ACTIVITY, NO_ACTIVITY };

class MotionSensor {
    private:
        int m_pin;

    public:
        MotionSensor(int pin);
        MotionState getState();
};
    