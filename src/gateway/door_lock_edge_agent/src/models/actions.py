from enum import Enum
from typing import Dict

class ActionType(Enum):
    doorlocks = 0

class DoorLockActionType(Enum):
    unlock = 0
    lock = 1

class DoorLockAction():
    def __init__(self, action_type: DoorLockActionType, message: str, device_id: str) -> None:
        self.action_type: DoorLockActionType = action_type
        self.message: str = message
        self.device_id: str = device_id