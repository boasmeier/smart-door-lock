from models.doorlock import DoorLock, DoorState, LockState

def get_all():
    """
    Returns all the door locks in this system.
    """

    # TODO: Read the devices from the database

    return [DoorLock(1135, DoorState.closed, LockState.locked).to_json(), DoorLock(1189, DoorState.open, LockState.unlocked).to_json()], 200