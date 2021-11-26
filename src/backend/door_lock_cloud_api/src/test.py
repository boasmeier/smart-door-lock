import json
from models.doorlock import DoorLock, DoorState, LockState
from models.events import DoorLockEvent, DoorLockEventType
event = DoorLockEvent(DoorLockEventType.intrusion, "", DoorLock(1, "iotlab", DoorState.open, LockState.unlocked, "test"))
json_file = {'event': 'intrusion', 'message': '', 'datetime': '2021-11-22T09:10:02.537903'}
print(json_file)

print(json.dumps(json_file))

json_file_2 = event.to_json()
print(json_file_2)

print(json.dumps(json_file_2))
