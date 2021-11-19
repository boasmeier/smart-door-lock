#pragma once

enum class DoorBellState { PRESSED, NOT_PRESSED };

class DoorBell {
    private:
        int m_pin;

    public:
        DoorBell(int pin);
        DoorBellState getState();
};

void handleRingEvent();