import logging
from models.actions import ActionSource, DoorLockAction, DoorLockActionType
from models.action_managers import DoorLockActionManager
from models.doorlock import DoorLock
from models.events import DoorLockEvent, DoorLockEventType
import telegram
from telegram import ReplyKeyboardMarkup, ReplyKeyboardRemove, Update, InlineKeyboardButton, InlineKeyboardMarkup
from telegram.ext import Updater, CommandHandler, CallbackContext, ConversationHandler, MessageHandler, Filters, \
    CallbackQueryHandler

TOKEN = '2003633335:AAESPEbqsoAFSodzIHcox6SunazxMVzw1ps'

# Define states
IDLE, OPEN_DOOR_REQUEST = range(2)  # Increment number with each state

# constants
OPEN_DOOR_YES = "open_door_yes"
OPEN_DOOR_NO = "open_door_no"

class TelegramService:
    _bot = telegram.Bot(token=TOKEN)
    _observers = []

    def __init__(self, chat_id: int = None, door_lock_action_manager: DoorLockActionManager = None):
        if chat_id is None:
            raise Exception("Chat-ID must be provided")
        self._chat_id = chat_id
        self.updater = Updater(token=TOKEN, use_context=True)
        self.last_doorlock = None
        self.door_lock_action_manager: DoorLockActionManager = door_lock_action_manager
        dispatcher = self.updater.dispatcher

        self.state = IDLE

        # Define Handlers
        dispatcher.add_handler(CallbackQueryHandler(self.open_door_handler))

        # Start the bot
        self.updater.start_polling()

    def __del__(self):
        self.updater.stop()

    def get_chat_id(self):
        return self._chat_id

    def set_chat_id(self, chat_id) -> None:
        self._chat_id = chat_id

    def get_name(self, username=False) -> str:
        name = self._bot.get_me()
        if username:
            return name.username
        else:
            return name.first_name

    def get_latest_chat_id(self) -> int:
        # First, write a message to the bot
        updates = self._bot.get_updates()
        chat_id = updates[0].message.from_user.id
        if chat_id is not None:
            print("Chat ID of latest message: " + str(chat_id))
        else:
            print("No chat-id has been found!")
        return chat_id

    def send_message(self, text, chat_id=None, reply_markup=None) -> None:
        logging.info(f"TelegramService - send_messge {text}")
        if chat_id is None:
            chat_id = self._chat_id

        self._bot.send_message(text=text, chat_id=chat_id, reply_markup=reply_markup)

    def main_handler(self, update, context):
        if update.message.text == "Yes":
            logging.info(f"User pressed open the door {self.last_doorlock.to_str()}")
            doorlock: DoorLock = self.last_doorlock
            self.door_lock_action_manager.execute_action(DoorLockAction(action_type=DoorLockActionType.unlock, message={}, doorlock=self.last_doorlock, source=ActionSource.telegram))
            update.message.reply_text(f'Okay, I will open the door {self.last_doorlock.name}!', reply_markup=ReplyKeyboardRemove())
            self.last_doorlock = None

        elif update.message.text == "No":
            logging.info(f"User pressed don't open the door")
            update.message.reply_text('Okay fine!', reply_markup=ReplyKeyboardRemove())
            self.last_doorlock = None

    def register(self, observer) -> None:
        self._observers.append(observer)

    def unregister(self, observer) -> None:
        self._observers.remove(observer)

    def notify(self) -> None:
        for observer in self._observers:
            observer.update()

    def _handle_ringing(self, doorlock: DoorLock, message: str):

        logging.info(f"_handle_ringing")

        self.send_yes_no_message(f'Ring, Ring! Are you sure to open the door: {doorlock.name}?', 'Open the door?')

    def _handle_intrusion(self, doorlock: DoorLock, message: str):
        logging.info(f"_handle_intrusion")

        # TODO: Maybe call the Police?
        self.send_message(f"Oh no! Someone broke into {doorlock.name}.")

    def _handle_suspiciousactivity(self, doorlock: DoorLock, message: str):
        logging.info(f"_handle_suspiciousactivity")
        self.send_message(f"Attention! Someone is moving in front of {doorlock.name}.")

    def handle_event(self, event: DoorLockEvent):
        logging.info(f"Received door lock event {event.event_type.name}")

        self.last_doorlock = event.doorlock

        if event.event_type == DoorLockEventType.ring:
            logging.info(f"Received door lock ring event")
            self._handle_ringing(event.doorlock, event.message)

        elif event.event_type == DoorLockEventType.intrusion:
            logging.info(f"Received door lock intrusion event")
            self._handle_intrusion(event.doorlock, event.message)

        elif event.event_type == DoorLockEventType.suspiciousactivity:
            logging.info(f"Received door lock suspiciousactivity event")
            self._handle_suspiciousactivity(event.doorlock, event.message)

    def set_state(self, state):
        self.state = state

    def send_yes_no_message(self, text, placeholder):
        keyboard = [
            [
                InlineKeyboardButton("Yes", callback_data=OPEN_DOOR_YES),
                InlineKeyboardButton("No", callback_data=OPEN_DOOR_NO),
            ]]
        reply_markup = InlineKeyboardMarkup(keyboard)
        self._bot.send_message(chat_id=self._chat_id, text=text, reply_markup=reply_markup)
        self.set_state(OPEN_DOOR_REQUEST)

    def open_door_handler(self, update: Update, context: CallbackContext) -> None:
        logging.info(f"Point reached state: {self.state}")
        if self.state == IDLE:
            self.send_message('Sorry, the message has already been handled')
            return

        self.set_state(IDLE)

        query = update.callback_query
        query.answer()

        if query.data == OPEN_DOOR_YES:
            self.send_message("Okay, I'll open the door")
            doorlock: DoorLock = self.last_doorlock
            self.door_lock_action_manager.execute_action(DoorLockAction(action_type=DoorLockActionType.unlock, message="", doorlock=self.last_doorlock))
        
        elif query.data == OPEN_DOOR_NO:
            self.send_message("Okay, I'll keep the door shut")
        else:
            self.send_message("Something went wrong. Query data: {}".format(query.data))

        logging.info(f"Second Point reached state: {self.state}")
