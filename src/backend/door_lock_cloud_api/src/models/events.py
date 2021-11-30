from enum import Enum
import json
import logging
from typing import Dict
from models.doorlock import DoorLock
import models.definitions as definitions
from datetime import datetime
class EventType(Enum):
    doorlocks = 0

class DoorLockEventType(Enum):
    intrusion = 0
    suspiciousactivity = 1
    ring = 2    
    movement = 3
    card = 4

class DoorLockEvent():
    def __init__(self, event_type: DoorLockEventType, message: str, doorlock: DoorLock, datetime_timestamp = None):
        self.event_type: DoorLockEventType = event_type
        self.message: str = message
        self.doorlock: DoorLock = doorlock
        if datetime_timestamp == None:
            self.datetime_timestamp = datetime.now()
        else:
            self.datetime_timestamp = datetime_timestamp

    def to_json(self) -> Dict:
        return {definitions.EVENT: self.event_type.name, definitions.MESSAGE: self.message, definitions.DATETIME: self.datetime_timestamp.isoformat()}

    @classmethod
    def from_json(cls, json: Dict, doorlock: DoorLock, timestamp: int):
        """
        Returns the DoorLock Event from json or None otherwise.
        """
        try:
            datetime_timestamp = datetime.fromtimestamp(float(timestamp))
            event_type = DoorLockEventType[json[definitions.EVENT]]
            message = json[definitions.MESSAGE]
            return cls(event_type, message, doorlock, datetime_timestamp)   

        except Exception as e:
            logging.error(f"DoorLockEvent - Unable to parse {json}, exception: {e}")
            return None