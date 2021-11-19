/*
  
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include "src/connection/WifiConnectionHandler.hpp"
#include "src/connection/MyMqttClient.hpp"
#include "src/connection/MqttTopics.hpp"
#include "src/config/secrets.hpp"
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

// the setup function runs once when you press reset or power the board
void setup()
{
    // initialize serial connection
    Serial.begin(115200);
    while (!Serial)
    {
        continue;
    }

    // set up connection to gateway
    connectToWifi();
    mqtt = new MyMqttClient(MQTT_HOST, MQTT_PORT);
    logSuccessfullConnectionToGateway();
    (*mqtt).m_mqttClient.onMessage(onMqttMessage);
    mqtt->subscribeTo(MqttTopics::UNLOCK);
    mqtt->subscribeTo(MqttTopics::LOCK);

    // set up card reader
    cardReader = new CardReader();
    Led greenLed(DOOR_LED_PIN_GREEN, String("green"));
    Led redLed(DOOR_LED_PIN_RED, String("red"));
    cardReaderHmi = new HumanMachineInterface(greenLed, redLed);

    // set up door
    Lock lock(LOCK_LED_PIN, DoorLockState::LOCKED);
    DoorSwitch doorSwitch(DOOR_SWITCH_PIN);
    DoorBell doorBell(DOORBELL_PIN);
    MotionSensor motionSensor(MOTION_SENSOR_PIN);
    door = new Door(lock, doorSwitch, doorBell, motionSensor);
}

// the loop function runs over and over again forever
void loop()
{
    /*
    mqtt->publish(MqttTopics::DOOR_STATE, "{ \"doorState\": \"open\" }");
    mqtt->publish(MqttTopics::LOCK_STATE, "{ \"lockState\": \"locked\" }");
  
    mqtt->publish(MqttTopics::INTRUSION_EVENT, "Intrusion event");
    mqtt->publish(MqttTopics::SUSPICIOUS_ACTIVITY_EVENT, "Suspicious Activity");
    mqtt->publish(MqttTopics::RING_EVENT, "Ring event");

    MQTT_INFO(mqtt, "Test logger %d", 42);
  
    if(door->getDoorBellState() == DoorBellState::PRESSED) {
        SERIAL_INFO("Ring event");
        mqtt->publish(MqttTopics::RING_EVENT, "Ring event");
    }
    door->toggleLock();
    if(door->getDoorSwitchState() == DoorSwitchState::OPEN) {
        SERIAL_INFO("Door open");
    }
    else {
        SERIAL_INFO("Door closed");
    }

    if(door->getLockState() == DoorLockState::UNLOCKED) {
        SERIAL_INFO("Door is unlocked");
        MQTT_INFO(mqtt, "Door is unlocked");
    }
    else {
        SERIAL_INFO("Door is locked");
        MQTT_INFO(mqtt, "Door is unlocked");
    }
    SERIAL_INFO("\n\n");
    */
    cardReader->read();
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
