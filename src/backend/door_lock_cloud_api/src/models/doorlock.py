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
    def __init__(self, deviceId: int, door_state: DoorState, lock_state: LockState):
        self.deviceId = deviceId
        self.door_state = door_state
        self.lock_state = lock_state
        self.site_id = 0

    def to_json(self) -> Dict:
        return {definitions.DOOR_STATE: self.door_state.name, definitions.LOCK_STATE: self.lock_state.name, definitions.DEVICEID : self.deviceId}