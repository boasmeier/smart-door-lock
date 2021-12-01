#include "MqttTopics.hpp"
#include "../config/DoorlockConfig.h"

#define DELIMITER "/"

// subscriber topics
const char *MqttTopics::UNLOCK = "gateway/1/action/unlock";
const char *MqttTopics::LOCK = "gateway/1/action/lock";

// publisher topics
const char *MqttTopics::INTRUSION_EVENT = "gateway/1/event/intrusion";
const char *MqttTopics::MOVEMENT_EVENT = "gateway/1/event/movement";
const char *MqttTopics::RING_EVENT = "gateway/1/event/ring";
const char *MqttTopics::CARD_EVENT = "gateway/1/event/card";
const char *MqttTopics::DOOR_STATE = "gateway/1/state/door";
const char *MqttTopics::LOCK_STATE = "gateway/1/state/lock";
const char *MqttTopics::LOG_TELEMETRY = "gateway/1/telemetry/logs";
