
from edge_logging.log_handler import LogHandler
from edge_logging.log_provider import LogProvider
from typing import List

class LogManager():
    """
    Gets the logs from all the LogProvider and stores it to all LogHandler's.
    """
    def __init__(self):
        self.log_providers: List[LogProvider] = []
        self.log_handlers: List[LogHandler] = []

    def add_log_provider(self, provider: LogProvider):
        """
        Add a  LogProvider which creates logs.
        """
        self.log_providers.append(provider)
        provider.register(self._inform_handlers)

    def add_log_handler(self, handler: LogHandler):
        """
        Add a  LogHandler which is interested in logs.
        """
        self.log_handlers.append(handler)

    def _inform_handlers(self, message: str):
        """
        Sends the messages to the handlers.
        """
        for log_handler in self.log_handlers:
            log_handler.handle_log(message)