from mqtt_client.client import MqttClient
import mqtt_client.topics as tp
from database.database import Database
from models.events import EventType, DoorLockEvent
from models.doorlock import DoorLock
import logging

class DoorLockEventManager():
    def __init__(self, mqtt_client: MqttClient, db: Database):
        logging.info(f"DoorLockEventManager create")
        self._handles = []
        self.mqtt_client = mqtt_client
        logging.info(f"DoorLockEventManager register callback")
        self.mqtt_client.register_callback(tp.event(EventType.doorlocks), self.on_event)
        self.db: Database = db

    def register_handle(self, handle):
        """
        Registers for updates on DoorLock Events. The handler function needs the following signature
        (DoorLockEvent) ->  None
        """
        self._handles.append(handle)

    def on_event(self, mosq, obj, msg):
        site_id: str = tp.get_site_id(msg.topic)
        device_id: str = tp.get_device_id(msg.topic)
        if not self.db.does_doorlock_exist(site_id, device_id):
            logging.error(f"DoorLockEventManager doorlock with: site_id: {site_id} and device_id: {device_id} does not exist")
        else:
            try:
                event_type: EventType = tp.get_doorlock_event_type(msg.topic)
            except Exception as e:
                logging.error(f"DoorLockEventManager unknown event: {msg.topic}, error: {e}")
                return

            doorlock: DoorLock = self.db.get_doorlock(site_id, device_id)

            event: DoorLockEvent = DoorLockEvent(event_type, msg.payload, doorlock)
            
            for handle in self._handles:
                handle(event)

