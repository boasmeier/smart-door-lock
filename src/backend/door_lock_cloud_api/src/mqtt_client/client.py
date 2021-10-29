class MqttClient():
    def __init__(self, address: str, port: int):
        pass

    def register_callback(self, topic, callback):
        """
        Registers a callback for receiving messages for this client.
        """
        pass

    def publish(self, topic: str, message: str):
        """
        Publishs a message to the passed topic.
        """
        pass