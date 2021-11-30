import logging
import logging.config
from typing import Dict, List
from arduino.arduino_publisher import ArduinoPublisher
from arduino.arduino_listener import ArduinoListener
from cloud.cloud_listener import CloudListener
from cloud.cloud_publisher import CloudPublisher
from edge_logging.log_handler import PythonLogHandler
from edge_logging.log_manager import LogManager
from edge_logging.log_provider import ArduinoMqttLogProvider
from models.suspicious_activity_detector import create_from_settings
from models.bell import BellHandler, DummyBell
from mqtt_client.client import MqttClient
from mqtt_client.paho_client import PahoClient
from settings import *
from settings import Settings
class EdgeAgent():
    def __init__(self, settings: Settings):
        self.setup_cloud_client(settings.mqtt_cloud)
        self.setup_gateway_client(settings.mqtt_gateway)
        self.setup_log_manager(settings.device_ids)
        self.setup_cloud_publisher(settings.site_id, settings.suspicious_activity)
        self.setup_bell()
        self.setup_arduino_listener(settings.device_ids)
        self.setup_arduino_publisher()
        self.setup_cloud_listener(settings.device_ids, settings.site_id)

    def setup_cloud_client(self, mqtt_cloud_settings: MqttServerSettings):
        self.mqtt_cloud_client: MqttClient = PahoClient(mqtt_cloud_settings.host, mqtt_cloud_settings.port)

    def setup_gateway_client(self, mqtt_gateway_settings: MqttServerSettings):
        self.mqtt_gateway_client: MqttClient = PahoClient(mqtt_gateway_settings.host, mqtt_gateway_settings.port)

    def setup_log_manager(self, device_ids: List[str]):
        """
        Setups the handling of logs.
        """
        self.log_manager = LogManager()
        self.log_manager.add_log_provider(ArduinoMqttLogProvider(self.mqtt_gateway_client, device_ids))
        self.log_manager.add_log_handler(PythonLogHandler("arduino"))

    def setup_arduino_listener(self, device_ids: List[str]):
        self.arduino_listener = ArduinoListener(self.mqtt_gateway_client, device_ids)
        self.arduino_listener.subscribe_to_states(self.cloud_publisher.handle_state)
        self.arduino_listener.subscribe_to_events(self.cloud_publisher.handle_event)
        self.arduino_listener.subscribe_to_events(self.bell_handler.handle_event)

    def setup_cloud_listener(self, device_ids: List[str], site_id: str):
        self.cloud_listener = CloudListener(self.mqtt_cloud_client, device_ids, site_id)
        self.cloud_listener.subscribe_to_actions(self.arduino_publisher.handle_action)

    def setup_cloud_publisher(self, site_id: str, suspicious_activity_settings: SuspiciousActivitySettings):
        self.cloud_publisher = CloudPublisher(self.mqtt_cloud_client, site_id, create_from_settings(suspicious_activity_settings))

    def setup_arduino_publisher(self):
        self.arduino_publisher = ArduinoPublisher(self.mqtt_gateway_client)

    def setup_bell(self):
        self.bell_handler = BellHandler(DummyBell())