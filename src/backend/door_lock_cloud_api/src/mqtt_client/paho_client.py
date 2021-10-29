import paho.mqtt.client as mqtt
from mqtt_client.client import MqttClient
import logging
import time

class PahoClient(MqttClient):
    def __init__(self, address: str, port: int):
        time.sleep(2)
        logging.info(f"Connecting PahoClient to {address}:{port}")
        self.address = address
        self.port = port
        self.callbacks = []
        self._client = mqtt.Client()

        self._client.on_connect = self.on_connect
        self._client.on_message = self.on_message
        self._client.loop_start()
        self._client.connect(address, port, 60)
        time.sleep(2)

    def register_callback(self, topic, callback):
        logging.info(f"Register callback topic: {topic}, callback: {callback}")
        self._client.message_callback_add(topic, callback)

    def on_connect(self, client, userdata, flags, rc):
        logging.info("MqttClient connected")
        client.subscribe("iotlab/#")
        logging.info("MqttClient connected with result code "+str(rc))
        client.publish("iotlab/lol", payload="Hallo test")

    def on_message(self, client, userdata, msg):
        logging.info(f"on_message - payload: {msg.topic} - message: {msg.payload}")