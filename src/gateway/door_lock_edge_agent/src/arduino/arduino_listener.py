import logging
from typing import List
from models.events import DoorLockEvent, DoorLockEventType
from models.states import DoorLockState
from mqtt_client.client import MqttClient

import mqtt_topics.gateway

class ArduinoListener():
    def __init__(self, mqtt_client: MqttClient, device_ids: List[str]):
        self.mqtt_client = mqtt_client  
        self.device_ids = device_ids
        self.state_subscribers = []
        self.event_subscribers = []
        self._register_topics()

    def subscribe_to_states(self, subscriber):
        """
        Subscribes to DoorLock state updates. Subscriber method : (DoorLockState)
        """
        self.state_subscribers.append(subscriber)

    def subscribe_to_events(self, subscriber):
        """
        Subscribes to DoorLock events. Subscriber method : (DoorLockEvent)
        """
        self.event_subscribers.append(subscriber)

    def _register_topics(self):
        # register to topics the arduino publishes to
        for device_id in self.device_ids:
            self.mqtt_client.subscribe(mqtt_topics.gateway.state(device_id))
            self.mqtt_client.register_callback(mqtt_topics.gateway.state(device_id), self._handle_state)
            self.mqtt_client.subscribe(mqtt_topics.gateway.event(device_id))
            self.mqtt_client.register_callback(mqtt_topics.gateway.event(device_id), self._handle_event)

    def _handle_state(self, client, userdata, msg):
        """
        Handles changes to the state.
        """
        for state_subscriber in self.state_subscribers:
            state_subscriber(DoorLockState(mqtt_topics.gateway.get_device_id_from_topic(msg.topic), mqtt_topics.gateway.get_state_type_from_topic(msg.topic), msg.payload))

    def _handle_event(self, client, userdata, msg):
        """
        Handles incoming events to the state.
        """
        for event_subscriber in self.event_subscribers:
            try:
                event_subscriber(DoorLockEvent(DoorLockEventType[mqtt_topics.gateway.get_state_type_from_topic(msg.topic)], msg.payload, mqtt_topics.gateway.get_device_id_from_topic(msg.topic)))
            except Exception as e:
                logging.error(f"ArduinoListener - unable to handle event: {e}")