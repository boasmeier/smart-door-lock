from telegram_bot.door_bot import DoorBot


class Main:
    bot = DoorBot(1335464798)

    def start(self):
        # self.bot.start()

        self.bot.register(self)

        # Get name of bot
        # self.bot.get_name()

        self.bot.trigger_open_door_procedure()

        while True:
            pass


main = Main()
main.start()
