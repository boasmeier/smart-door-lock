/*
 * MqttMessage.cpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#include <Arduino.h>
#include "MqttMessage.hpp"

MqttMessage::MqttMessage(String topic, String msg) : m_topic(topic), m_message(msg) {

};

String MqttMessage::getTopic() {
    return m_topic;
};

String MqttMessage::getMessage() {
    return m_message;
};