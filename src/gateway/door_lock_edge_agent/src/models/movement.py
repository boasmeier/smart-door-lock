import datetime

class Movement():
    def __init__(self):
        self.date = datetime.datetime.now()

    def is_older_than(self, older_than_in_s: s) -> bool:
        return (datetime.datetime.now() - self.date) > datetime.timedelta(seconds = older_than_in_s)