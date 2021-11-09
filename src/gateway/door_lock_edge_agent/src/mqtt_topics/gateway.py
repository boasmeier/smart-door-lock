from models.actions import DoorLockAction

DOOR_STATE = "doorState"
LOCK_STATE = "lockState"
DOOR_LOCKS = "doorlocks"
GATEWAY = "gateway"
STATE = "state"
SITEID = "siteId"
DEVICEID = "deviceId"
LOCK = "lock"
DOOR = "door"
EVENT = "event"
ACTION = "action"
TELEMETRY = "telemetry"
GATEWAY = "gateway"
LOGS = "logs"

DELIMITER = "/"
WILDCARD = "+"


def logs(device_id: str) -> str:
    """
    Returns the topic for logs for this device_id.
    """
    return GATEWAY + DELIMITER + device_id  + DELIMITER + TELEMETRY + DELIMITER + LOGS       

def get_device_id_from_topic(topic: str) -> str:
    """
    Parses the device_id from the given topic.
    """
    return topic.split(DELIMITER)[1]  

def get_state_type_from_topic(topic: str) -> str:
    """
    Parses the state_type from the given topic.
    """
    return topic.split(DELIMITER)[3]  

def get_event_type_from_topic(topic: str) -> str:
    """
    Parses the event type from the given topic.
    """
    return topic.split(DELIMITER)[3]  

def state(device_id: str) -> str:
    """
    Returns the topic to subscribe to the state of the doorlock with the provided device_id.
    """
    return GATEWAY + DELIMITER + device_id + DELIMITER + STATE + DELIMITER + WILDCARD

def event(device_id: str) -> str:
    """
    Returns the topic to subscribe to the events of the doorlock with the provided device_id.
    """
    return GATEWAY + DELIMITER + device_id + DELIMITER +  EVENT + DELIMITER + WILDCARD

def action(action: DoorLockAction) -> str:
    """
    Returns the topic to publish to the actions of the doorlock with the provided device_id.
    """
    return GATEWAY + DELIMITER + action.device_id + DELIMITER +  ACTION + DELIMITER + action.action_type.name