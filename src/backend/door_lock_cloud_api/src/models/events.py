from enum import Enum
from typing import Dict
from models.doorlock import DoorLock

class EventType(Enum):
    doorlocks = 0

class DoorLockEventType(Enum):
    intrusion = 0
    suspiciousactivity = 1
    ring = 2

class DoorLockEvent():
    def __init__(self, event_type: DoorLockEventType, message: str, doorlock: DoorLock):
        self.event_type: DoorLockEventType = event_type
        self.message: Dict = message
        self.doorlock: DoorLock = doorlock