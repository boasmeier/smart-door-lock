import paho.mqtt.client as mqtt
from mqtt_client.client import MqttClient
import logging
import time


class MqttClient():
    def __init__(self, address: str, port: int):
        pass

    def register_callback(self, callback):
        """
        Registers a callback for receiving messages for this client.
        """
        pass


class PahoClient(MqttClient):
    def __init__(self, address: str, port: int):
        logging.info("Before connecting")
        time.sleep(5)
        logging.info("After connecting")

        self.address = address
        self.port = port
        self.callbacks = []
        self._client = mqtt.Client()

        self._client.on_connect = self._on_connect
        self._client.on_message = self._on_message
        self._client.connect(address, port, 60)

    def register_callback(self, callback):
        self.callbacks.append(callback)

    # The callback for when the client receives a CONNACK response from the server.
    def _on_connect(self, client, userdata, flags, rc):
        logging.info("_on_connect")

        print("Connected with result code "+str(rc))
        # Subscribing in on_connect() means that if we lose the connection and
        # reconnect then subscriptions will be renewed.
        client.subscribe("$SYS/#")

    # The callback for when a PUBLISH message is received from the server.
    def _on_message(self, client, userdata, msg):
        logging.info("_on_message")
        print(msg.topic+" "+str(msg.payload))
