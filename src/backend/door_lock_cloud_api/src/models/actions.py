from enum import Enum
from typing import Dict
import models.definitions as definitions
from datetime import datetime
from models.doorlock import DoorLock
import logging

class ActionType(Enum):
    doorlocks = 0

class ActionSource(Enum):
    api = 0
    telegram = 1
    phone = 2
    unknown = 3
class DoorLockActionType(Enum):
    unlock = 0
    lock = 1

class DoorLockAction():
    def __init__(self, action_type: DoorLockActionType, message: str, doorlock: DoorLock, source: ActionSource = ActionSource.unknown, datetime_timestamp = None) -> None:
        self.action_type: DoorLockActionType = action_type
        self.message: str = message
        self.doorlock: DoorLock = doorlock
        self.source = source
        if datetime_timestamp == None:
            self.datetime_timestamp = datetime.now()
        else:
            self.datetime_timestamp = datetime_timestamp

    def to_json(self) -> Dict:
        return {definitions.ACTION: self.action_type.name, definitions.MESSAGE: self.message, definitions.DATETIME: self.datetime_timestamp.isoformat(), definitions.SOURCE: self.source.name}

    @classmethod
    def from_json(cls, json: Dict, doorlock: DoorLock, timestamp: int):
        """
        Returns the DoorLock Object from json or None otherwise.
        """
        try:
            datetime_timestamp = datetime.fromtimestamp(float(timestamp))
            action_type = DoorLockActionType[json[definitions.ACTION]]
            message = json[definitions.MESSAGE]
            source = ActionSource[json[definitions.SOURCE]]
            return cls(action_type, message, doorlock, source, datetime_timestamp)   

        except Exception as e:
            logging.error(f"DoorLockAction - Unable to parse {json}, exception: {e}")
            return None