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


def on_connect(client, userdata, flags, rc):
    logging.info("on_connect")
    client.subscribe("hallo_test")
    logging.info("Connected with result code "+str(rc))
    client.publish("hallo_test", payload="Hallo test")

def on_message(client, userdata, msg):
    logging.info("GOt merssage")
    logging.info(f"message: {msg}")

class PahoClient(MqttClient):
    def __init__(self, address: str, port: int):
        logging.info("Before connecting")
        time.sleep(5)
        logging.info("After connecting")

        self.address = address
        self.port = port
        self.callbacks = []
        self._client = mqtt.Client()

        self._client.on_connect = on_connect
        self._client.on_message = on_message
        self._client.loop_start()
        self._client.connect(address, port, 60)

    def register_callback(self, callback):
        self.callbacks.append(callback)