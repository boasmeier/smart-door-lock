/*
 * doorlock_controller.ino
 * Created on 2021-10-10
 * 
 * Copyright(c) 2021 HSLU.
 * This software is the proprietary information of HSLU. 
 * Author: Boas Meier boas.meier@stud.hslu.ch  
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include "src/connection/WifiConnectionHandler.hpp"
#include "src/connection/PahoMqttClient.hpp"
#include "src/connection/MqttTopics.hpp"
#include "src/config/Secrets.hpp"
#include "src/config/DoorlockConfig.h"
#include "src/logger/MqttLogger.hpp"
#include "src/logger/SerialLogger.hpp"

#include "src/door/Lock.hpp"
#include "src/door/DoorSwitch.hpp"
#include "src/door/DoorBell.hpp"
#include "src/door/MotionSensor.hpp"
#include "src/door/Door.hpp"

#include "src/card_reader/CardReader.hpp"
#include "src/card_reader/HumanMachineInterface.hpp"
#include "src/card_reader/Led.hpp"

#include "src/lib/timer/Timer.h"

// define global variables in .ino file inside setup function
WifiConnectionHandler *connHandl;
PahoMqttClient *mqtt;
Door *door;
HumanMachineInterface *cardReaderHmi;

Timer *ledTimer;
Timer *blinkTimer;
Timer *stopTimer;

// the setup function runs once when you press reset or power the board
void setup()
{
    // initialize serial connection
    Serial.begin(9600);
    while (!Serial)
    {
        continue;
    }


    // set up timers for non-blocking led handling
    ledTimer = new Timer(1000, ledOffCallback, true);
    blinkTimer = new Timer(1000/HMI_BLINK_FREQUENCY, ledToggleCallback, false);
    stopTimer = new Timer(1000/HMI_BLINK_FREQUENCY * 6, ledBlinkStopCallback, true);


    // set up connection to gateway
    connectToWifi();
    mqtt = new PahoMqttClient(MQTT_HOST, MQTT_PORT);
    logSuccessfullConnectionToGateway();
    mqtt->m_mqttClient.onMessage(onMqttMessage);
    mqtt->subscribeTo(MqttTopics::UNLOCK);
    mqtt->subscribeTo(MqttTopics::LOCK);


    // set up card reader
    Led greenLed(DOOR_LED_PIN_GREEN, String("green"));
    Led redLed(DOOR_LED_PIN_RED, String("red"));
    cardReaderHmi = new HumanMachineInterface(greenLed, redLed);
    CardReader cardReader;


    // set up door
    Lock lock(LOCK_LED_PIN, DoorLockState::LOCKED);
    DoorSwitch doorSwitch(DOOR_SWITCH_PIN_OPEN, DOOR_SWITCH_PIN_CLOSE);
    DoorBell doorBell(DOORBELL_PIN);
    MotionSensor motionSensor(MOTION_SENSOR_PIN);
    door = new Door(lock, doorSwitch, doorBell, motionSensor, cardReader);
}



// the loop function runs over and over again forever
void loop()
{
    mqtt->poll();
    mqtt->handleMqttMessage();

    ledTimer->Update();
    blinkTimer->Update();
    stopTimer->Update();

    door->read();
    door->handleDoorBellRingEvent();
    door->handleDoorSwitchOpenedEvent();
    door->handleDoorSwitchClosedEvent();
    door->handleMotionDetectionEvent();
    
    delay(100);
}

void connectToWifi()
{
    char ssid[] = SECRET_SSID;
    char pass[] = SECRET_PASS;
    connHandl = new WifiConnectionHandler();
    connHandl->scanNetworks();
    connHandl->connectWPA2(ssid, pass);
}

void logSuccessfullConnectionToGateway()
{
    MQTT_INFO(mqtt, "Arduino connected to network with ssid: %s", connHandl->getSsid());
    MQTT_INFO(mqtt, "IP Address of arduino: %s", connHandl->getIp().c_str());
    byte mac[6];
    connHandl->getMac(mac);
    MQTT_INFO(mqtt, "MAC address of arduino: %02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    byte bssid[6];
    connHandl->getBssid(bssid);
    MQTT_INFO(mqtt, "BSSID: %02X:%02X:%02X:%02X:%02X:%02X", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
    MQTT_INFO(mqtt, "Arduino connected to broker %s:%d", MQTT_HOST, MQTT_PORT);
}
