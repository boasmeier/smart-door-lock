#pragma once

#include <Arduino.h>

class MqttMessageHandler {
    public:
        static void handleMessage(String topic, String msg);
    private:
        static void handleUnlock();
        static void handleLock();
};