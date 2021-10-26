from typing import List
from models.doorlock import DoorLock, DoorState, LockState

class Database():
    def __init__(self):
        pass
    
    def does_doorlock_exist(self, siteId: str, deviceId: str) -> bool:
        """
        Returns whether a doorlock exists or not. Will just return if in the database both door and lock state are present.
        """
        pass

    def get_doorlocks(self) -> List[DoorLock]:
        """
        Returns all the doorlocks.
        """
        pass
    
    def get_doorlocks(self, siteId: str) -> List[DoorLock]:
        """
        Returns all the doorlocks in the database with the passed siteId.
        """
        pass

    def get_doorlock(self, siteId: str, deviceId: str) -> DoorLock:
        """
        Returns all the doorlock in the database with the passed siteId and deviceId.
        """
        pass

    def set_doorstate(self, siteId: str, deviceId: str, doorState: DoorState):
        """
        Sets the doorState for the passed door lock.
        """
        pass

    def set_lockstate(self, siteId: str, deviceId: str, lockState: LockState):
        """
        Sets the lockState for the passed door lock.
        """
        pass
    