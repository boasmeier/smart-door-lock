from models.action_managers import MqttDoorLockActionManager, DoorLockActionManager
from mqtt_client.client import MqttClient
from mqtt_client.paho_client import PahoClient
from models.actions import DoorLockActionType, DoorLockAction
from models.doorlock import DoorLock, DoorState, LockState
from database.database import Database
from database.redis_database import RedisDatabase
from models import definitions
from typing import Dict
import logging

db: Database = RedisDatabase("doorlock-database", 6379)
mqtt_client: MqttClient = PahoClient("mqtt-broker", 1883)

doorlock_action_manager: DoorLockActionManager = MqttDoorLockActionManager(mqtt_client, db)

def get_all_from_site(site_id: str):
    """
    Returns all the door locks with a site_id in this system.
    """

    return [doorlock.to_json() for doorlock in db.get_doorlocks(siteId=site_id)], 200


def get_device_from_site(site_id: str, device_id: str):
    """
    Returns the door lock wit the site_id and device_id.
    """
    if db.does_doorlock_exist(site_id, device_id):
        return db.get_doorlock(site_id, device_id).states_to_json()

    else:
        return None, 404


def post_doorlock_action(site_id: str, device_id: str, body: Dict):
    """
    Executes a doorlock action for a certain doorlock.
    """
    action_str: str = body[definitions.ACTION]

    if db.does_doorlock_exist(site_id, device_id):
        doorlock: DoorLock =  db.get_doorlock(site_id, device_id)

        try:
            doorlock_action_type: DoorLockActionType = DoorLockActionType[action_str]
            doorlock_action_manager.execute_action(DoorLockAction(doorlock_action_type, "", doorlock))
            return f"DoorLockAction: {doorlock_action_type.name} for {doorlock.to_str()} in progress", 200

        except Exception as e:
            logging.error(f"doorlocks: unable to parse action {e}")
            return f"action [{action_str}] not found", 404

    else:
        return "Doorlock not found", 404

def put_device_from_site(site_id: str, device_id: str, body: Dict):
    """
    Sets the new doorlock with name in this system.
    """
    if definitions.NAME not in body:
        return f"Missing payload {definitions.NAME}", 400

    db.set_name(site_id, device_id, body[definitions.NAME])

    return f"Updated Name to {body[definitions.NAME]}", 200
