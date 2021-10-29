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
        self.arduinoLogger = logging.getLogger('arduino')

    def setup_cloud_client(self):
        self.mqtt_cloud_client: MqttClient = PahoClient(CLOUD_MQTT_HOST, CLOUD_MQTT_PORT)

    def setup_gateway_client(self):
        self.mqtt_gateway_client: MqttClient = PahoClient(GATEWAY_MQTT_HOST, GATEWAY_MQTT_PORT)
        # register to topics the arduino publishes to
        self.mqtt_gateway_client.register_callback("gateway/1/event/intrusion", self.forward_intrusion_event_to_cloud)
        self.mqtt_gateway_client.register_callback("gateway/1/event/suspiciousactivity", self.forward_suspicious_activity_event_to_cloud)
        self.mqtt_gateway_client.register_callback("gateway/1/event/ring", self.forward_ring_event_to_cloud)
        self.mqtt_gateway_client.subscribe("gateway/1/state/door")
        self.mqtt_gateway_client.subscribe("gateway/1/state/lock")
        self.mqtt_gateway_client.register_callback("gateway/1/telemetry/logs", self.handle_log_telemetry_from_arduino)

        # register to tipics the cloud publishes to
        self.mqtt_gateway_client.subscribe("iotlab/doorlocks/1/action/unlock")
        self.mqtt_gateway_client.subscribe("iotlab/doorlocks/1/action/lock")

    def forward_ring_event_to_cloud(self, client, userdata, msg):
        logging.info(f"Forward to cloud - topic: {msg.topic} - message: {msg.payload}")
        self.mqtt_cloud_client.publish("iotlab/doorlocks/2/event/ring", "Ring event from device 1")

    def forward_intrusion_event_to_cloud(self, client, userdata, msg):
        logging.info(f"Forward to cloud - topic: {msg.topic} - message: {msg.payload}")
        self.mqtt_cloud_client.publish("iotlab/doorlocks/2/event/intrusion", "Ring event from device 1")

    def forward_suspicious_activity_event_to_cloud(self, client, userdata, msg):
        logging.info(f"Forward to cloud - topic: {msg.topic} - message: {msg.payload}")
        self.mqtt_cloud_client.publish("iotlab/doorlocks/2/event/suspiciousactivity", "Ring event from device 1")

    def handle_log_telemetry_from_arduino(self, client, userdata, msg):
        logging.info(f"Handle arduino telemetry - topic: {msg.topic} - message: {msg.payload}")
        self.arduinoLogger.info(msg)
    


if __name__ == "__main__":
    logging.config.fileConfig(path.join(path.dirname(path.abspath(__file__)), 'logger.conf'))
    agent = CloudAgent("arduino")
    while(1):
        continue