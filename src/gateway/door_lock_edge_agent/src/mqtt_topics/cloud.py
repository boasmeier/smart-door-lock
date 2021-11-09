from models.events import DoorLockEvent
from models.states import DoorLockState


DOOR_STATE = "doorState"
LOCK_STATE = "lockState"
DOOR_LOCKS = "doorlocks"
GATEWAY = "gateway"
STATE = "state"
SITEID = "siteId"
DEVICEID = "deviceId"
LOCK = "lock"
DOOR = "door"
EVENT = "event"
ACTION = "action"

DELIMITER = "/"
WILDCARD = "+"

def door_locks(site_id: str) -> str:
    return site_id + DELIMITER +  DOOR_LOCKS

def door_state(site_id: str, device_id: str) -> str:
    return door_locks(site_id) + DELIMITER + device_id + DELIMITER + STATE + DELIMITER + DOOR

def lock_state(site_id: str, device_id: str) -> str:
    return door_locks(site_id) + DELIMITER + device_id + DELIMITER + STATE + DELIMITER + LOCK

def get_site_id(doorlocks_topic: str) -> str:
    return str.split(doorlocks_topic, DELIMITER)[0]

def get_device_id(doorlocks_topic: str) -> str:
    return str.split(doorlocks_topic, DELIMITER)[2]

def get_action_type(doorlocks_topic: str) -> str:
    return str.split(doorlocks_topic, DELIMITER)[4]

def event(site_id: str, event: DoorLockEvent) -> str:
    return site_id + DELIMITER + DOOR_LOCKS + DELIMITER + event.device_id + DELIMITER + EVENT + DELIMITER + event.event_type.name

def state(site_id: str, state: DoorLockState) -> str:
    return site_id + DELIMITER + DOOR_LOCKS + DELIMITER + state.device_id + DELIMITER + STATE + DELIMITER + state.type

def action(site_id: str, device_id: id) -> str:
    return site_id + DELIMITER + DOOR_LOCKS + DELIMITER + device_id + DELIMITER + ACTION + DELIMITER + WILDCARD
