from telegram_bot import Bot


class Main:
    bot = Bot(-708897855)

    def start(self):
        self.bot.register(self)

        # Get name of bot
        self.bot.get_name()

        # Send Message to the latest chat-ID
        self.bot.send_message("Hello, I'm ready to start")

        while True:
            pass

    def update(self):
        print("I got  called")


main = Main()
main.start()
