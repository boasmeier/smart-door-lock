import logging
import logging.config
from os import path
from typing import Dict, List
from mqtt_client.client import MqttClient
from mqtt_client.paho_client import PahoClient
import mqtt_client.topics as tp
from settings import *

class CloudAgent():
    def __init__(self, device_ids: List[str]):
        self.setup_cloud_client()
        self.setup_gateway_client()
        self.device_ids: List[str] = device_ids

    def setup_cloud_client(self):
        self.mqtt_cloud_client: MqttClient = PahoClient(CLOUD_MQTT_HOST, CLOUD_MQTT_PORT)

    def setup_gateway_client(self):
        self.mqtt_gateway_client: MqttClient = PahoClient(GATEWAY_MQTT_HOST, GATEWAY_MQTT_PORT)
        self.mqtt_gateway_client.subscribe("gateway/1/event/intrusion")
        self.mqtt_gateway_client.subscribe("gateway/1/event/suspiciousactivity")
        self.mqtt_gateway_client.subscribe("gateway/1/event/ring")
        self.mqtt_gateway_client.subscribe("gateway/1/state/door")
        self.mqtt_gateway_client.subscribe("gateway/1/state/lock")
        self.mqtt_gateway_client.subscribe("gateway/1/telemetry/logs")

if __name__ == "__main__":
    logging.config.fileConfig(path.join(path.dirname(path.abspath(__file__)), 'logger.conf'))
    agent = CloudAgent("arduino")
    while(1):
        continue