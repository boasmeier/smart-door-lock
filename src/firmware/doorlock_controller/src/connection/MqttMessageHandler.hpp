/*
 * MqttMessageHandler.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#pragma once

#include <Arduino.h>

class MqttMessageHandler {
    public:
        static void handleMessage(String topic, String msg);
    private:
        static void handleUnlock();
        static void handleLock();
};