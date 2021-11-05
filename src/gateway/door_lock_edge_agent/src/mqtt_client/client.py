class MqttClient():
    def __init__(self, address: str, port: int):
        pass

    def register_callback(self, topic, callback):
        """
        Registers a callback for receiving messages for this client.
        """
        pass

    def subscribe(self, topic):
        """
        Subscribes to a topic.
        """
        pass

    def publish(self, topic, msg):
        """
        Publish a message to a topic.
        """
        pass