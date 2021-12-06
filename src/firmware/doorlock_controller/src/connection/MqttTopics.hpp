/*
 * MqttTopics.hpp
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch 
*/
#ifndef MQTT_TOPICS_H_
#define MQTT_TOPICS_H_

class MqttTopics {
  public:
    // subscriber topics
    static const char *UNLOCK;
    static const char *LOCK;

    // publisher topics
    static const char *INTRUSION_EVENT;
    static const char *MOVEMENT_EVENT;
    static const char *CARD_EVENT;
    static const char *RING_EVENT;
    static const char *DOOR_STATE;
    static const char *LOCK_STATE;
    static const char *LOG_TELEMETRY;
};

#endif // MQTT_TOPICS_H
