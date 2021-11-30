from enum import Enum
from typing import Dict
import datetime
class EventType(Enum):
    doorlocks = 0

class DoorLockEventType(Enum):
    intrusion = 0
    suspiciousactivity = 1
    ring = 2
    movement = 3
    card = 4

class DoorLockEvent():
    def __init__(self, event_type: DoorLockEventType, message: str, device_id: str):
        self.event_type: DoorLockEventType = event_type
        self.message: Dict = message
        self.device_id: str = device_id
        self.date = datetime.datetime.now()

    def is_older_than(self, older_than_in_s: int) -> bool:
        return (datetime.datetime.now() - self.date) > datetime.timedelta(seconds = older_than_in_s)