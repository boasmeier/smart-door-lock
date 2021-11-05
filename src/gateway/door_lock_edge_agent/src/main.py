import logging.config 
from os import path
from edge_agent import EdgeAgent
import configparser
from settings import Settings

def __read_config(self) -> configparser.ConfigParser:
    config = configparser.ConfigParser()
    config.read("edge_agent.conf")
    return config


if __name__ == "__main__":
    logging.config.fileConfig(path.join(path.dirname(path.abspath(__file__)), 'logger.conf'))
    agent = EdgeAgent(Settings(__read_config("edge_agent.conf")))
    while(1):
        continue