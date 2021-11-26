#pragma once

enum class DoorSwitchState { OPEN, CLOSED };

class DoorSwitch {
    private:
        int m_pinOpen;
        int m_pinClose;

    public:
        DoorSwitch(int pinOpen, int pinClose);
        DoorSwitchState getState();
        void handleDoorOpenedEvent();
        void handleDoorClosedEvent();
};

void doorSwitchOpenedISR();
void doorSwitchClosedISR();
void triggerIntrusionEvent();

static volatile byte doorOpenendEventCount = 0;
static volatile byte doorClosedEventCount = 0;
    