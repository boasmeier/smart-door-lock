import logging
import RPi.GPIO as GPIO 
import threading
import time
from models.events import DoorLockEvent, DoorLockEventType

class Bell():
    """
    A ringing bell.
    """

    def ring(self, time_in_s: int):
        """
        Rings the bell for a certain time.
        """
        pass

class DummyBell(Bell):
    """
    A bell which logs instead of actually ringing.
    """

    def ring(self, time_in_s: int):
        """
        Writes a log if someone is ringing.
        """
        logging.info(f"Ring, Ring for {time_in_s} seconds")

class PiezoBell(Bell):
    """
    A bell which rings with the connected piezo speaker.
    """
    def __init__(self, pin: int) -> None:
        self.pin = pin
        GPIO.setmode(GPIO.BOARD)

    def ring(self, time_in_s: int):
        """
        Rings the piezo bell.
        """
        logging.info(f"Piezo Bell: Ring, Ring for {time_in_s} seconds")
        ring = threading.Thread(target=self._ring, args=(time_in_s,))
        ring.start()

    def _ring(self, time_in_s: int):
        f_ding = 600
        f_dong = (f_ding * 2) // 3

        GPIO.setmode(GPIO.BOARD)        
        GPIO.setup(self.pin, GPIO.OUT)
        pwm = GPIO.PWM(self.pin, f_ding)   
        pwm.start(50)                      
        time.sleep(time_in_s//2)
        pwm.stop() 
        GPIO.cleanup()                     

        GPIO.setmode(GPIO.BOARD)        
        GPIO.setup(self.pin, GPIO.OUT)
        pwm2 = GPIO.PWM(self.pin, f_dong)   
        pwm2.start(50)                      
        time.sleep(time_in_s//2)
        pwm2.stop() 
        GPIO.cleanup()                                     

class BellHandler():
    def __init__(self, bell: Bell):
        self.bell = bell
    
    def handle_event(self, event: DoorLockEvent):
        if event.event_type == DoorLockEventType.ring:
            self.bell.ring(5)
