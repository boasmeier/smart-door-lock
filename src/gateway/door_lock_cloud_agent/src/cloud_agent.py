import logging
import logging.config
from os import path
from typing import Dict, List
from mqtt_client.client import MqttClient
from mqtt_client.paho_client import PahoClient
import mqtt_client.topics as tp

class CloudAgent():
    def __init__(self, device_ids: List[str]):
        self.mqtt_cloud_client: MqttClient = PahoClient("127.0.0.1", 1883)
        self.mqtt_gateway_client: MqttClient = PahoClient("127.0.0.1", 1884)
        self.device_ids: List[str] = device_ids

if __name__ == "__main__":
    logging.config.fileConfig(path.join(path.dirname(path.abspath(__file__)), 'logger.conf'))
    agent = CloudAgent("arduino")
    while(1):
        continue