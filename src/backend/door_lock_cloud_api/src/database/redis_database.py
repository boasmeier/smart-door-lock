from typing import List
from models.doorlock import DoorLock, DoorState, LockState
import models.definitions as definitions
import redis
import json
from database.database import Database
import logging

class RedisDatabase(Database):
    delimiter: str = ":"

    def __init__(self, host: str, port: int):
        self._host = host
        self._port = port
        logging.info(f"RedisDatabase {host}:{port} starting")
        self._client = redis.Redis(host, port, 0)
    
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
        self._client.set(self._get_doorstate_key(siteId, deviceId), json.dumps({definitions.DOOR_STATE: doorState.name}))

    def set_lockstate(self, siteId: str, deviceId: str, lockState: LockState):
        """
        Sets the lockState for the passed door lock.
        """
        self._client.set(self._get_lockstate_key(siteId, deviceId), json.dumps({definitions.LOCK_STATE: lockState.name}))

    def _base_key(self, site_id: str, device_id: str) -> str:
        """
        Returns the base key: [site_id]:doorlocks:[device_id]
        """ 
        return site_id + RedisDatabase.delimiter + definitions.DOOR_LOCKS + RedisDatabase.delimiter + device_id

    def _get_lockstate_key(self, siteId: str, deviceId: str):
        return self._base_key(siteId, deviceId) + RedisDatabase.delimiter + definitions.STATE + RedisDatabase.delimiter + definitions.LOCK
       
    def _get_doorstate_key(self, siteId: str, deviceId: str):
        return self._base_key(siteId, deviceId) + RedisDatabase.delimiter + definitions.STATE + RedisDatabase.delimiter + definitions.DOOR

    