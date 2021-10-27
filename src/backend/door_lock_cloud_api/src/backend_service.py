import logging
from database.redis_database import RedisDatabase 
from database.database import Database
from services.telegram_service import TelegramService
from models.events import DoorLockEvent
from models.event_managers import DoorLockEventManager
from mqtt_client.client import MqttClient
from mqtt_client.paho_client import PahoClient
import mqtt_client.topics as tp
import json
from typing import Dict, List
from models.doorlock import LockState, DoorState
import models.definitions as definitions

def on_state_updated(mosq, obj, msg):
    logging.info(f"State updated {msg.payload}")

class StateUpdater():
    def __init__(self, db: Database):
        self.db: Database = db
    
    def on_lockstate_updated(self, mosq, obj, msg):
        logging.info(f"StateUpdater on_lockstate_updated - update with {msg.payload}")
        json_value: Dict = json.loads(msg.payload)

        try:
            self.db.set_lockstate(tp.get_site_id(msg.topic), tp.get_device_id(msg.topic), LockState[json_value[definitions.LOCK_STATE]])
        except Exception as e:
            logging.error(f"StateUpdater on_lockstate_updated - unable to parse {json_value} - e: {e}")

    def on_doorstate_updated(self, mosq, obj, msg):
        logging.info(f"StateUpdater on_doorstate_updated - update with {msg.payload}")
        json_value: Dict = json.loads(msg.payload)

        try:
            self.db.set_doorstate(tp.get_site_id(msg.topic), tp.get_device_id(msg.topic), DoorState[json_value[definitions.DOOR_STATE]])
        except Exception as e:
            logging.error(f"StateUpdater on_doorstate_updated - unable to parse {json_value} - e: {e}")

class BackendService():
    def __init__(self, site_ids: List[str]):
        self.mqtt_client: MqttClient = PahoClient("mqtt-broker", 1883)
        self.site_ids: List[str] = site_ids
        self.db: Database = RedisDatabase("doorlock-database", 6379)
        self.state_updater: StateUpdater = StateUpdater(self.db)
        self.doorlock_event_manager: DoorLockEventManager = DoorLockEventManager(self.mqtt_client, self.db)
        #self.doorlock_event_manager.register_handle(self.handle_events)
        #TODO: Add Telegram Service here
        #TelegramService(1335464798) -> Niklas
        self.telegram_services: List[TelegramService] = [TelegramService(-708897855)]
        self.register_callbacks()

    def register_callbacks(self):
        for site_id in self.site_ids:
            self.mqtt_client.register_callback(tp.lock_state(site_id, "+"), self.state_updater.on_lockstate_updated)
            self.mqtt_client.register_callback(tp.door_state(site_id, "+"), self.state_updater.on_doorstate_updated)

        for telegram_service in self.telegram_services:
            self.doorlock_event_manager.register_handle(telegram_service.handle_event)
       
    def handle_events(self, event: DoorLockEvent):
        logging.info(f"BackendService received {event.event_type.name} event for doorlock {event.doorlock.to_str()}")