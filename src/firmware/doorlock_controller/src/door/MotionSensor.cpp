#include "SPI.h"
#include "MotionSensor.hpp"
#include "../connection/MyMqttClient.hpp"
#include "../connection/MqttTopics.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"

MotionSensor::MotionSensor(int pin) : m_pin(pin) {
    pinMode(m_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(m_pin), motionDetectionISR, RISING);
}

MotionState MotionSensor::getState() {
    int state = digitalRead(m_pin);
    return state ? MotionState::ACTIVITY : MotionState::NO_ACTIVITY;
}

void MotionSensor::handleMotionDetection() {
    if(motionDetectedEventCount > 0) {
        motionDetectedEventCount--;
        SERIAL_INFO("Motion detected");
        MQTT_INFO(mqtt, "Motion detected");
        SERIAL_INFO("Motion detection event count: %d", motionDetectedEventCount);
        mqtt->publish(MqttTopics::MOVEMENT_EVENT, "");
    }
    //SERIAL_INFO("Motion detection event count: %d", motionDetectedEventCount);
}

static volatile unsigned long previousTime = 0;
static volatile unsigned long enterTime = 0;
void motionDetectionISR() {
    enterTime = millis();
    if(enterTime-previousTime > 2000) {
        motionDetectedEventCount++;
        previousTime = enterTime;
    }
}