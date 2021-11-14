#pragma once

enum class DoorSwitchState { OPEN, CLOSED };

class DoorSwitch {
    private:
        int m_pin;

    public:
        DoorSwitch(int pin);
        DoorSwitchState getState();
};

void handleDoorOpened();
void handleDoorClosed();
void triggerIntrusionEvent();
    