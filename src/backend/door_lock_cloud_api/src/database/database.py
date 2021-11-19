from typing import List
from models.actions import DoorLockAction
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

    def set_name(self, siteId: str, deviceId: str, name: str):
        """
        Sets the name for the passed door lock.
        """
        pass

    def set_doorlock_action(self, action: DoorLockAction) :
        """
        Stores a doorlock action for a certain doorlock in the database.
        """
        pass

    def get_doorlock_actions(self, siteId: str, deviceId: str) -> List[DoorLockAction]:
        """
        Returns all the doorlock actions in the database with the passed siteId and deviceId.
        """
        pass
    