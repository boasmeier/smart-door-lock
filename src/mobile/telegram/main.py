from telegram_bot import Bot

bot = Bot(1335464798)

# Get name of bot
bot.get_name()

# Send Message to the latest chat-ID
bot.send_message("Hello, I'm ready to start")

while True:
    pass
