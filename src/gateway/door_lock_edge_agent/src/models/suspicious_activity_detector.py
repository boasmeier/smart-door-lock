import logging
from typing import Dict 
from models.events import DoorLockEvent, DoorLockEventType

class SuspiciousActivityDetector():
    """
    Says if this movement event is suspicious or not!
    """
    def is_suspicous_activity(self, event: DoorLockEvent) -> bool:
        pass

class TimeBasedSuspiciousActivityDetector():

    def __init__(self, timeframe_in_s: int, amount_of_movements: int):
        self.timeframe_in_s = amount_of_movements
        self.amount_of_movements = amount_of_movements
        self.past_movements: Dict = 

    """
    Says if this movement event is suspicious or not based on a simple timeout, if 
    """
    def is_suspicous_activity(self, event: DoorLockEvent) -> bool:
        self._clean_up_old_events()

    def _clean_up_old_events(self):
        for key, value in past_movements.items():
            #TODO: Clean up all events which are too old
            pass

class BellHandler():
    def __init__(self, bell: Bell):
        self.bell = bell
    
    def handle_event(self, event: DoorLockEvent):
        if event.event_type == DoorLockEventType.ring:
            self.bell.ring(5)
