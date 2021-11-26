#ifndef _MQTT_MESSAGE_H
#define _MQTT_MESSAGE_H

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

#endif