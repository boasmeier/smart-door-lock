import telegram
from telegram import InlineKeyboardButton, InlineKeyboardMarkup, Update
from telegram.ext import Updater, CallbackContext, CallbackQueryHandler

TOKEN = '2003633335:AAESPEbqsoAFSodzIHcox6SunazxMVzw1ps'

# Define states
IDLE, OPEN_DOOR_REQUEST = range(2)  # Increment number with each state

# constants
OPEN_DOOR_YES = "open_door_yes"
OPEN_DOOR_NO = "open_door_no"
DOOR = range(1)  # Increment number with each state


class DoorBot:
    _bot = telegram.Bot(token=TOKEN)
    _observers = []

    def __init__(self, chat_id: int = None):
        if chat_id is None:
            raise Exception("Chat-ID must be provided")
        self._chat_id = chat_id
        self.updater = Updater(token=TOKEN, use_context=True)

        dispatcher = self.updater.dispatcher
        self.state = IDLE

        # Define Handlers
        dispatcher.add_handler(CallbackQueryHandler(self.open_door_handler))

        # Start bot
        self.updater.start_polling()

    def __del__(self):
        self.updater.stop()

    def register(self, observer) -> None:
        self._observers.append(observer)

    def unregister(self, observer) -> None:
        self._observers.remove(observer)

    def notify(self) -> None:
        for observer in self._observers:
            observer.update()

    def set_state(self, state):
        self.state = state

    def set_chat_id(self, chat_id) -> None:
        self._chat_id = chat_id

    def get_chat_id(self):
        return self._chat_id

    def get_name(self, username=False) -> str:
        name = self._bot.get_me()
        if username:
            return name.username
        else:
            return name.first_name

    def send_message(self, text, chat_id=None) -> None:
        if chat_id is None:
            chat_id = self._chat_id

        self._bot.send_message(text=text, chat_id=chat_id)

    def trigger_open_door_procedure(self, chat_id=None):
        self.send_yes_no_message('Are you sure to open the door?', 'Open the door?', chat_id)
        self.set_state(OPEN_DOOR_REQUEST)

    def send_yes_no_message(self, text, placeholder, chat_id=None):
        if chat_id is None:
            chat_id = self.get_chat_id()
        keyboard = [
            [
                InlineKeyboardButton("Yes", callback_data=OPEN_DOOR_YES),
                InlineKeyboardButton("No", callback_data=OPEN_DOOR_NO),
            ]]
        reply_markup = InlineKeyboardMarkup(keyboard)
        self._bot.send_message(chat_id=chat_id, text=text, reply_markup=reply_markup)
        self.set_state(OPEN_DOOR_REQUEST)

    def open_door_handler(self, update: Update, context: CallbackContext) -> None:
        print("Point reached")
        if self.state == IDLE:
            self.send_message('Sorry, the message has already been handled')
            return

        query = update.callback_query
        query.answer()

        if query.data == OPEN_DOOR_YES:
            self.send_message("Okay, I'll open the door")
        elif query.data == OPEN_DOOR_NO:
            self.send_message("Okay, I'll keep teh door shut")
        else:
            self.send_message("Something went wrong. Query data: {}".format(query.data))

        self.set_state(IDLE)
