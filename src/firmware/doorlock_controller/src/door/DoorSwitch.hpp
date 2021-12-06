/*
 * DoorSwitch.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef DOOR_SWITCH_H_
#define DOOR_SWITCH_H_

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

#endif // DOOR_SWITCH_H_  