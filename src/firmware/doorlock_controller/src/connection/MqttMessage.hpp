/*
 * MqttMessage.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef MQTTMESSAGE_H_
#define MQTTMESSAGE_H_

#include <Arduino.h>

class MqttMessage {
    private:
        String m_topic;
        String m_message;
        
    public:
        MqttMessage(String topic, String msg);
        String getTopic();
        String getMessage();
        
};

#endif // MQTTMESSAGE_H_