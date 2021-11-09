from typing import List
from models.actions import DoorLockAction, DoorLockActionType
from mqtt_client.client import MqttClient

import mqtt_topics.cloud

class CloudListener():
    def __init__(self, mqtt_client: MqttClient, device_ids: List[str], site_id: str):
        self.mqtt_client = mqtt_client  
        self.device_ids = device_ids
        self.site_id = site_id
        self.action_subscribers = []
        self._register_topics()

    def subscribe_to_actions(self, subscriber):
        """
        Subscribes to DoorLock action updates. Subscriber method : (DoorLockAction)
        """
        self.action_subscribers.append(subscriber)

    def _register_topics(self):
        # register to topics the cloud publishes to
        for device_id in self.device_ids:
            self.mqtt_client.subscribe(mqtt_topics.cloud.action(self.site_id, device_id))
            self.mqtt_client.register_callback(mqtt_topics.cloud.action(self.site_id, device_id), self._handle_action)

    def _handle_action(self, client, userdata, msg):
        """
        Handles changes to the state.
        """
        for action_subscriber in self.action_subscribers:
            action_subscriber(DoorLockAction(DoorLockActionType[mqtt_topics.cloud.get_action_type(msg.topic)], msg.payload, mqtt_topics.cloud.get_device_id(msg.topic)))