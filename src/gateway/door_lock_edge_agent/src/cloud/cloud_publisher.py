from models.suspicious_activity_detector import SuspiciousActivityDetector, TimeBasedSuspiciousActivityDetector
from mqtt_client.client import MqttClient
from models.events import DoorLockEvent, DoorLockEventType
import mqtt_topics.cloud
from models.states import DoorLockState
import logging

class CloudPublisher():
    """
    Publishes messages to the cloud.
    """
    def __init__(self, mqtt_client: MqttClient, site_id: str, suspicious_activity_detector: SuspiciousActivityDetector):
        self.mqtt_client = mqtt_client
        self.site_id = site_id
        self.suspicious_activity_detector: SuspiciousActivityDetector = suspicious_activity_detector

    def handle_event(self, event: DoorLockEvent):
        logging.info(f"Forward to cloud - event: {event.event_type.name} - message: {event.message}")
        if self._should_event_be_forwarded_to_cloud(event):
            self.mqtt_client.publish(mqtt_topics.cloud.event(self.site_id, event), event.message)

        event: DoorLockEvent = self._check_suspicious_activity(event)
        if event is not None:
            logging.info("Detected a suspicious event - publish to cloud")
            self.mqtt_client.publish(mqtt_topics.cloud.event(self.site_id, event), event.message)


    def handle_state(self, state: DoorLockState):
        logging.info(f"Forward to cloud - state: {state.type} for lock {state.device_id} - payload: {state.payload}")
        self.mqtt_client.publish(mqtt_topics.cloud.state(self.site_id, state), state.payload)

    def _should_event_be_forwarded_to_cloud(self, event: DoorLockEvent) -> bool:
        if event.event_type is  DoorLockEventType.movement:
            return False
        return True

    def _check_suspicious_activity(self, event: DoorLockEvent) -> DoorLockEvent:
        if self.suspicious_activity_detector.is_suspicous_activity(event):
            return DoorLockEvent(DoorLockEventType.suspiciousactivity, message = "", device_id=event.device_id)

        return None
    
