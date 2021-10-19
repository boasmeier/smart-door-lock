import telegram
from telegram import ReplyKeyboardMarkup, ReplyKeyboardRemove
from telegram.ext import Updater, CommandHandler, CallbackContext, ConversationHandler, MessageHandler, Filters

TOKEN = '2003633335:AAESPEbqsoAFSodzIHcox6SunazxMVzw1ps'

DOOR = range(1)  # Increment number with each state


class Bot:
    _bot = telegram.Bot(token=TOKEN)

    def __init__(self, chat_id: int = None):
        if chat_id is None:
            raise Exception("Chat-ID must be provided")
        self._chat_id = chat_id
        self.updater = Updater(token=TOKEN, use_context=True)
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

    def send_message(self, text, chat_id=None) -> None:
        if chat_id is None:
            chat_id = self._chat_id

        self._bot.send_message(text=text, chat_id=chat_id)

    # --- HANDLERS BELOW HERE --- #

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
            update.message.reply_text("I'm opening the door now", reply_markup=ReplyKeyboardRemove())
        elif context.match.string == 'No':
            update.message.reply_text("Okay, I keep the door shut", reply_markup=ReplyKeyboardRemove())
        else:
            print("Something went wrong")
