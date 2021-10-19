from telegram_bot import Bot

bot = Bot()

# Get name of bot
bot.get_name()

# Get Chat-ID of latest message
chat_id = bot.get_latest_chat_id()

# Send Message to the latest chat-ID
bot.send_message("Hallo bob", chat_id)

# Set this chat to the active chat
bot.set_chat_id(chat_id)
