#pragma once

class MqttTopics {
  public:
    // subscriber topics
    static const char *UNLOCK;
    static const char *LOCK;

    // publisher topics
    static const char *INTRUSION_EVENT;
    static const char *SUSPICIOUS_ACTIVITY_EVENT;
    static const char *CARD_EVENT;
    static const char *RING_EVENT;
    static const char *DOOR_STATE;
    static const char *LOCK_STATE;
    static const char *LOG_TELEMETRY;
};
