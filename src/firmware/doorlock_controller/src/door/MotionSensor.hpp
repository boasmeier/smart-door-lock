/*
 * MotionSensor.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef MOTION_SENSOR_H_
#define MOTION_SENSOR_H_

enum class MotionState { ACTIVITY, NO_ACTIVITY };

class MotionSensor {
    private:
        int m_pin;

    public:
        MotionSensor(int pin);
        MotionState getState();
        void handleMotionDetection();
};


void motionDetectionISR();
    
static volatile byte motionDetectedEventCount = 0;

#endif // MOTION_SENSOR_H_