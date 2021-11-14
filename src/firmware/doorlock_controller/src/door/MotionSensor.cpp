#include "SPI.h"
#include "MotionSensor.hpp"
#include "../connection/MyMqttClient.hpp"
#include "../connection/MqttTopics.hpp"
#include "../logger/SerialLogger.hpp"
#include "../logger/MqttLogger.hpp"

MotionSensor::MotionSensor(int pin) : m_pin(pin) {
    pinMode(m_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(m_pin), handleMovementDetection, RISING);
}

MotionState MotionSensor::getState() {
    int state = digitalRead(m_pin);
    return state ? MotionState::ACTIVITY : MotionState::NO_ACTIVITY;
}

void handleMovementDetection() {
    // TODO: Check wheter it is suspicious movement
    SERIAL_INFO("Movement detected");
}