import logging

class LogHandler():
    """
    Stores or handles the logs it receives.
    """

    def handle_log(log_message: str):
        """
        Handles the logs.
        """
        pass

class PythonLogHandler():
    """
    Stores the logs to a python logger with a certain name.
    """
    def __init__(self, logger_name) -> None:
        """
        :param file_name The name of the log file.
        """
        self.arduinoLogger = logging.getLogger(logger_name)


    def handle_log(self, log_message: str):
        """
        Handles the logs.
        """
        self.arduinoLogger.info(log_message)

