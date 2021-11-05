class DoorLockState():
    def __init__(self, device_id: str, type: str, payload: str) -> None:
        self.device_id = device_id
        self.type = type
        self.payload = payload