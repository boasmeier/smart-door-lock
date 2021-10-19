import telegram

DEFAULT_CHAT_ID = 1335464798  # Chat ID of the Creator of the iot-bot


class Bot:
    _bot = telegram.Bot(token='2003633335:AAESPEbqsoAFSodzIHcox6SunazxMVzw1ps')

    def __init__(self, chat_id=DEFAULT_CHAT_ID):
        self._chat_id = chat_id

    def set_chat_id(self, chat_id) -> None:
        self._chat_id = chat_id

    def get_name(self, username=False) -> str:
        name = self._bot.get_me()
        print("First name: " + name.first_name)
        print("username: " + name.username)
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
