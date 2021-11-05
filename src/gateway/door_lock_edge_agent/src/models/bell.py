import logging

from models.events import DoorLockEvent, DoorLockEventType

class Bell():
    """
    A ringing bell.
    """

    def ring(self, time_in_s: int):
        """
        Rings the bell for a certain time.
        """
        pass

class DummyBell(Bell):
    """
    A bell which logs instead of actually ringing.
    """

    def ring(self, time_in_s: int):
        """
        Writes a log if someone is ringing.
        """
        logging.info(f"Ring, Ring for {time_in_s} seconds")

class BellHandler():
    def __init__(self, bell: Bell):
        self.bell = bell
    
    def handle_event(self, event: DoorLockEvent):
        if event.event_type == DoorLockEventType.ring:
            self.bell.ring(5)
