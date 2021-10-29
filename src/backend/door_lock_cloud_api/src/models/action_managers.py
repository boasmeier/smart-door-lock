from models.actions import DoorLockAction
from mqtt_client.client import MqttClient
import mqtt_client.topics as tp
from database.database import Database
from models.events import EventType, DoorLockEvent
from models.doorlock import DoorLock
import logging

class DoorLockActionManager():
    """
    Defines a manager who can execute a certain DoorLock Action.
    """

    def execute_action(self, action: DoorLockAction):
        """
        Executes the passed DoorLockAction.
        """
        pass

class MqttDoorLockActionManager():
    """
    Executes a Door Lock Action over the passed MqttClient.
    """
    def __init__(self, mqtt_client: MqttClient, db: Database):
        logging.info(f"DoorLockActionManager create")
        self._handles = []
        self.mqtt_client = mqtt_client
        self.db: Database = db

    def execute_action(self, action: DoorLockAction):
        """
        Executes the passed DoorLockAction over MQTT.
        """
        self.mqtt_client.publish(tp.doorlock_action(action), action.message)

