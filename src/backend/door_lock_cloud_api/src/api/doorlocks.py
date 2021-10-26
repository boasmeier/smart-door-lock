from models.doorlock import DoorLock, DoorState, LockState
from database.database import Database
from database.redis_database import RedisDatabase

db: Database = RedisDatabase("doorlock-database", 6379)

def get_all_from_site(site_id: str):
    """
    Returns all the door locks with a site_id in this system.
    """

    return [doorlock.to_json() for doorlock in db.get_doorlocks(siteId=site_id)], 200


def get_device_from_site(site_id: str, device_id: str):
    """
    Returns the door lock wit the site_id and device_id.
    """
    if db.does_doorlock_exist(site_id, device_id):
        return db.get_doorlock(site_id, device_id).states_to_json()

    else:
        return None, 404