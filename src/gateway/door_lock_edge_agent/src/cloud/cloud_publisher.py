from mqtt_client.client import MqttClient
from models.events import DoorLockEvent
import mqtt_topics.cloud
from models.states import DoorLockState
import logging

class CloudPublisher():
    """
    Publishes messages to the cloud.
    """
    def __init__(self, mqtt_client: MqttClient, site_id: str):
        self.mqtt_client = mqtt_client
        self.site_id = site_id

    def handle_event(self, event: DoorLockEvent):
        logging.info(f"Forward to cloud - event: {event.event_type.name} - message: {event.message}")
        self.mqtt_client.publish(mqtt_topics.cloud.event(self.site_id, event), event.message)

    def handle_state(self, state: DoorLockState):
        logging.info(f"Forward to cloud - state: {state.type} for lock {state.device_id} - payload: {state.payload}")
        self.mqtt_client.publish(mqtt_topics.cloud.state(self.site_id, state), state.payload)