import logging
from typing import Dict
from settings import SuspiciousActivitySettings 
from models.events import DoorLockEvent, DoorLockEventType
import json


class SuspiciousActivityDetector():
    """
    Says if this movement event is suspicious or not!
    """
    def is_suspicous_activity(self, event: DoorLockEvent) -> bool:
        pass

class TimeBasedSuspiciousActivityDetector():
    def __init__(self, timeframe_in_s: int, amount_of_movements: int):
        self.timeframe_in_s = timeframe_in_s
        self.amount_of_movements = amount_of_movements
        self.past_movements: Dict = {}

    """
    Says if this movement event is suspicious or not based on a simple timeout, if 
    """
    def is_suspicous_activity(self, event: DoorLockEvent) -> bool:
        self._clean_up_old_events()
        if not self._is_relevant_event(event):  
            return False

        if self._is_cleanup_event(event):
            logging.info("TimeBasedSuspiciousActivityDetector - received clean up event")
            self._clean_up_events_for_device_id(event.device_id)
            return False

        self._add_new_event(event)
        suspicious: bool =  self._is_movement_in_front_of_device_suspicious(event.device_id)

        if suspicious:
            self._clean_up_events_for_device_id(event.device_id)

        return suspicious

    def _clean_up_old_events(self):
        # Clean up all events which are too old
        new_movements: Dict = {}
        for device_id, movements in self.past_movements.items():
            movements_for_device_id = [movement for movement in movements if not movement.is_older_than(self.timeframe_in_s)]
            new_movements[device_id] = movements_for_device_id
        self.past_movements = new_movements

    def _is_relevant_event(self, event: DoorLockEvent) -> bool:
        if event.event_type is DoorLockEventType.movement:
            return True

        elif event.event_type is DoorLockEventType.card:
            return True
        
        return False

    def _is_cleanup_event(self, event):
        if event.event_type is DoorLockEventType.card:
            if json.loads(event.message)["authorized"] == True:
                return True

        return False

    def _add_new_event(self, event: DoorLockEvent) -> bool:
        if event.device_id not in self.past_movements:
            self.past_movements[event.device_id] = []
        
        self.past_movements[event.device_id].append(event)

    def _is_movement_in_front_of_device_suspicious(self, device_id: int) -> bool:
        return len(self.past_movements[device_id]) >= self.amount_of_movements

    def _clean_up_events_for_device_id(self, device_id: int):
        self.past_movements[device_id] = []

def create_from_settings(settings: SuspiciousActivitySettings) -> SuspiciousActivityDetector:
    if settings.detector == "timebased":
        logging.info(f"settings: {settings.params}")
        return TimeBasedSuspiciousActivityDetector(int(settings.params["timebasedtimeframeins"]), int(settings.params["timebasedamountofmovments"]))

    return None
