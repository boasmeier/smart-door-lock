from enum import Enum
from typing import Dict
import models.definitions as definitions
import logging

class DoorState(Enum):
    open = 0
    closed = 1

class LockState(Enum):
    locked = 0
    unlocked = 1

class DoorLock():
    """
    Represents a door lock with a unique deviceid, a lock and a door state.
    """
    def __init__(self, device_id: int, site_id: str, door_state: DoorState, lock_state: LockState):
        self.device_id = device_id
        self.door_state = door_state
        self.lock_state = lock_state
        self.site_id = site_id
        self.name = f"{site_id} Door {device_id}"

    def to_json(self) -> Dict:
        return {definitions.DOOR_STATE: self.door_state.name, definitions.LOCK_STATE: self.lock_state.name, definitions.DEVICEID : self.device_id}

    def states_to_json(self) -> Dict:
        return {definitions.DOOR_STATE: self.door_state.name, definitions.LOCK_STATE: self.lock_state.name}

    def to_str(self) -> str:
        return f"DoorLock: device_id: {self.device_id}, site_id: {self.site_id}, door_state: {self.door_state.name}, lock_state: {self.lock_state.name}"

    @classmethod
    def from_json(json: Dict, siteId: str, deviceId: str):
        """
        Returns the DoorLock Object from json or None otherwise.
        """
        try:
            device_id = deviceId
            site_id = siteId
            door_state = DoorState(json[definitions.DOOR_STATE])    
            lock_state = LockState(json[definitions.LOCK_STATE]) 
            return DoorLock(device_id, site_id, door_state, lock_state)   

        except:
            logging.error(f"DoorLock - Unable to parse {json}")
            return None