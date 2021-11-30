import configparser
from typing import List, Dict

class MqttServerSettings():
    def __init__(self, host: str, port:int) -> None:
        self.host = host
        self.port = int(port)

class SuspiciousActivitySettings():
    def __init__(self, detector: str, params:Dict) -> None:
        self.detector = detector
        self.params = params

class Settings():
    def __init__(self, config: configparser.ConfigParser):
        self.mqtt_gateway = MqttServerSettings(str(config["Gateway"]["MqttHost"]), int(config["Gateway"]["MqttPort"]))
        self.mqtt_cloud = MqttServerSettings(str(config["Cloud"]["MqttHost"]), int(config["Cloud"]["MqttPort"]))
        self.suspicious_activity = SuspiciousActivitySettings(str(config["SuspiciousActivityDetector"]["Detector"]), dict(config.items('SuspiciousActivityDetectorParams')))
        self.site_id = config["Site"]["SiteId"]
        self.device_ids: List[str] = config["Site"]["DeviceIds"].split(",")
