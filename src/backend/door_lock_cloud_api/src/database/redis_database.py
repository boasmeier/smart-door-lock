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

    def does_doorlock_exist(self, siteId: str, deviceId: str) -> bool:
        """
        Returns whether a doorlock exists or not. Will just return if in the database both door and lock state are present.
        """
        return len(self._client.keys((self._get_doorstate_key(siteId, deviceId)))) == 1 and len(self._client.keys((self._get_lockstate_key(siteId, deviceId)))) == 1
    
    def get_doorlocks(self) -> List[DoorLock]:
        """
        Returns all the doorlocks.
        """
        pass
    
    def get_doorlocks(self, siteId: str) -> List[DoorLock]:
        """
        Returns all the doorlocks in the database with the passed siteId.
        """
        doorlocks: List[DoorLock] = []
        for device_id in self._get_all_device_ids(siteId):
            doorlocks.append(self.get_doorlock(siteId, device_id))
        return doorlocks

    def get_doorlock(self, siteId: str, deviceId: str) -> DoorLock:
        """
        Returns all the doorlock in the database with the passed siteId and deviceId.
        """
        return DoorLock(deviceId, siteId, DoorState[json.loads(self._client.get(self._get_doorstate_key(siteId, deviceId)))[definitions.DOOR_STATE]], LockState[json.loads(self._client.get(self._get_lockstate_key(siteId, deviceId)))[definitions.LOCK_STATE]], json.loads(self._client.get(self._get_name_key(siteId, deviceId)))[definitions.NAME])

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

    def _get_name_key(self, siteId: str, deviceId: str):
        return self._base_key(siteId, deviceId) + RedisDatabase.delimiter + definitions.NAME

    def _get_all_device_ids(self, siteId: str) -> List[str]:
        return set.union(set([self._parse_device_id(str(key)) for key in self._client.keys((self._get_lockstate_key(siteId, "*")))]) , set([self._parse_device_id(str(key)) for key in self._client.keys((self._get_doorstate_key(siteId, "*")))]))

    def _parse_device_id(self, key: str) -> str:
        logging.info(f"key: {key}")
        logging.info(f"split: {key.split(RedisDatabase.delimiter)}")

        return key.split(RedisDatabase.delimiter)[2]
    