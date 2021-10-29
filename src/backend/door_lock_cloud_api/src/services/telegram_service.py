import logging
from models.doorlock import DoorLock
from models.events import DoorLockEvent, DoorLockEventType
import telegram
from telegram import ReplyKeyboardMarkup, ReplyKeyboardRemove
from telegram.ext import Updater, CommandHandler, CallbackContext, ConversationHandler, MessageHandler, Filters, CallbackQueryHandler

TOKEN = '2003633335:AAESPEbqsoAFSodzIHcox6SunazxMVzw1ps'

DOOR = range(1)  # Increment number with each state

class TelegramService:
    _bot = telegram.Bot(token=TOKEN)
    _observers = []

    def __init__(self, chat_id: int = None):
        if chat_id is None:
            raise Exception("Chat-ID must be provided")
        self._chat_id = chat_id
        self.updater = Updater(token=TOKEN, use_context=True)
        self.last_doorlock = None
        dispatcher = self.updater.dispatcher

        # Define Handlers
        start_handler = CommandHandler('start', self._start)
        dispatcher.add_handler(start_handler)

        door_handler = ConversationHandler(
            entry_points=[CommandHandler('open', self._open_door_check)],
            allow_reentry=True,
            states={
                DOOR: [MessageHandler(Filters.regex('^(Yes|No)$'), self._handle_door)]
            },
            fallbacks=[CommandHandler('cancel', self._cancel)])
        self.updater.dispatcher.add_handler(door_handler)

        # message handler
        self.updater.dispatcher.add_handler(MessageHandler(Filters.text, self.main_handler))

        # suggested_actions_handler
        self.updater.dispatcher.add_handler(CallbackQueryHandler(self.main_handler, pass_chat_data=True, pass_user_data=True))

        # Start the bot
        self.updater.start_polling()

    def __del__(self):
        self.updater.stop()

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
            #TODO: Send Unlock Action
            logging.info(f"User pressed open the door {self.last_doorlock.to_str()}")
            doorlock: DoorLock = self.last_doorlock
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

        self.send_message(
           f"Hello someone is ringing at {doorlock.name}, do you want to open the door?",
            reply_markup=ReplyKeyboardMarkup([['Yes', 'No']],
                                             one_time_keyboard=True,
                                             input_field_placeholder='Open the door?'))
        

    def _handle_intrusion(self, doorlock: DoorLock, message: str):
        logging.info(f"_handle_intrusion")

        #TODO: Maybe call the Police?
        self.send_message( f"Oh no! Someone broke into {doorlock.name}.")          

    def _handle_suspiciousactivity(self, doorlock: DoorLock, message: str):
        logging.info(f"_handle_suspiciousactivity")
        self.send_message( f"Attention! Someone is moving in front of {doorlock.name}.")         

    def handle_event(self, event: DoorLockEvent):
        # --- HANDLERS BELOW HERE --- #
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

    def _start(self, update, context):
        context.bot.send_message(chat_id=update.effective_chat.id, text="I am already running")

    def _cancel(self, update, context: CallbackContext) -> int:
        update.message.reply_text('Bye! I hope we can talk again some day.', reply_markup=ReplyKeyboardRemove())

        return ConversationHandler.END

    def _open_door_check(self, update, context: CallbackContext) -> range:
        reply_keyboard = [['Yes', 'No']]

        update.message.reply_text(
            'Are you sure to open the door?',
            reply_markup=ReplyKeyboardMarkup(reply_keyboard,
                                             one_time_keyboard=True,
                                             input_field_placeholder='Open the door?'))

        return DOOR

    def _handle_door(self, update, context: CallbackContext):
        if context.match.string == 'Yes':
            print("Door opening")
            self.notify()
            update.message.reply_text("I'm opening the door now", reply_markup=ReplyKeyboardRemove())
        elif context.match.string == 'No':
            update.message.reply_text("Okay, I keep the door shut", reply_markup=ReplyKeyboardRemove())
        else:
            print("Something went wrong")
