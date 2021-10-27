import logging
from models.events import DoorLockEventType, EventType
from models import definitions

delimiter = "/"
wildcard = "+"

def door_locks(site_id: str) -> str:
    return site_id + delimiter +  definitions.DOOR_LOCKS

def event(event_type: EventType) -> str:
    return wildcard + delimiter + event_type.name + delimiter + wildcard + delimiter + definitions.EVENT + delimiter + wildcard

def door_state(site_id: str, device_id: str) -> str:
    return door_locks(site_id) + delimiter + device_id + delimiter + definitions.STATE + delimiter + definitions.DOOR

def lock_state(site_id: str, device_id: str) -> str:
    return door_locks(site_id) + delimiter + device_id + delimiter + definitions.STATE + delimiter + definitions.LOCK

def get_site_id(doorlocks_topic: str) -> str:
    return str.split(doorlocks_topic, delimiter)[0]

def get_device_id(doorlocks_topic: str) -> str:
    return str.split(doorlocks_topic, delimiter)[2]

def get_doorlock_event_type(doorlocks_topic: str) -> DoorLockEventType:
    return DoorLockEventType[str.split(doorlocks_topic, delimiter)[4]]