from models.bell import PiezoBell
import logging.config
from os import path

if __name__ == "__main__":
    logging.config.fileConfig(path.join(path.dirname(path.abspath(__file__)), 'logger.conf'))
    bell = PiezoBell(12)
    bell.ring(3)
   
