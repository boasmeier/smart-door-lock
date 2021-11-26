from enum import Enum
from typing import Dict

class EventType(Enum):
    doorlocks = 0

class DoorLockEventType(Enum):
    intrusion = 0
    suspiciousactivity = 1
    ring = 2
    movement = 3

class DoorLockEvent():
    def __init__(self, event_type: DoorLockEventType, message: str, device_id: str):
        self.event_type: DoorLockEventType = event_type
        self.message: Dict = message
        self.device_id: str = device_id