from enum import Enum
from typing import Dict

from models.doorlock import DoorLock

class ActionType(Enum):
    doorlocks = 0

class DoorLockActionType(Enum):
    unlock = 0
    lock = 1

class DoorLockAction():
    def __init__(self, action_type: DoorLockActionType, message: Dict, doorlock: DoorLock) -> None:
        self.action_type: DoorLockActionType = action_type
        self.message: Dict = message
        self.doorlock: DoorLock = doorlock