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