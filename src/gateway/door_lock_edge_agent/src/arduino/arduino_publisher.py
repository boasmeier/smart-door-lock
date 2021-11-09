from mqtt_client.client import MqttClient
from models.actions import DoorLockAction
import mqtt_topics.gateway
from models.states import DoorLockState
import logging

class ArduinoPublisher():
    """
    Publishes messages to the arduino devices.
    """
    def __init__(self, mqtt_client: MqttClient):
        self.mqtt_client = mqtt_client

    def handle_action(self, action: DoorLockAction):
        logging.info(f"Forward to gateway - action: {action.action_type.name} - message: {action.message}")
        self.mqtt_client.publish(mqtt_topics.gateway.action(action), action.message)