import logging

from mqtt_client.client import MqttClient
from typing import List
import mqtt_topics.gateway

class LogProvider():
    """
    Provides logs to the registered methods.
    """

    def register(self, callback):
        """
        Registers a method which is interested for logs.
        :param callback The callback function where the logs get sent to -> Signature looks like this def(str).
        """
        pass


class ArduinoMqttLogProvider():
    """
    Provides logs from the Arduino via MQTT.
    """

    def __init__(self, mqtt_client: MqttClient, device_ids: List[str]):
        self.mqtt_client = mqtt_client
        self.device_ids = device_ids
        self.callbacks = []
        self._register_mqtt_callback()

    def register(self, callback):
        """
        Registers a method which is interested for logs.
        :param callback The callback function where the logs get sent to -> Signature looks like this def(str).
        """
        self.callbacks.append(callback)
    
    def _register_mqtt_callback(self):
        """
        Subscribes for all devices to the MQTT Callback.
        """
        for device_id in self.device_ids:            
            self.mqtt_client.subscribe(mqtt_topics.gateway.logs(device_id))
            self.mqtt_client.register_callback(mqtt_topics.gateway.logs(device_id), self._handle_logs)

    def _fire_callback(self, message: str):
        for callback in self.callbacks:
            callback(message)

    def _handle_logs(self, client, userdata, msg):
        """
        Mqtt Callback function.
        """
        logging.info(f"Handle arduino telemetry - topic: {msg.topic} - message: {msg.payload}")

        device_id = mqtt_topics.gateway.get_device_id_from_topic(msg.topic)
        message = f"[{device_id}] {msg.payload}"
        logging.info(f"Provide following message: {message}")

        self._fire_callback(message)



              