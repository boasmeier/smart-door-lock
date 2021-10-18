from enum import Enum
from typing import Dict
import models.definitions as definitions

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
    def __init__(self, device_id: int, door_state: DoorState, lock_state: LockState):
        self.device_id = device_id
        self.door_state = door_state
        self.lock_state = lock_state
        self.site_id = 0

    def to_json(self) -> Dict:
        return {definitions.DOOR_STATE: self.door_state.name, definitions.LOCK_STATE: self.lock_state.name, definitions.DEVICEID : self.deviceId}

    @classmethod
    def from_json(json: Dict, siteId: str, deviceId: str):
        """
        Returns the DoorLock Object from json or None otherwise.
        """
        try:
            device_id = device_id
            site_id = site_id
            door_state = DoorState(json[definitions.DOOR_STATE])    
            lock_state = LockState(json[definitions.LOCK_STATE]) 
            return DoorLock(device_id, site_idm, door_state, lock_state)   

        except:
            logging.error(f"DoorLock - Unable to parse {json}")
            return None