from abc import ABC, abstractmethod


class Logger(ABC):

    @abstractmethod
    def log_start_process(self, date: int) -> None:
        pass

    @abstractmethod
    def log_end_process(self, date: int) -> None:
        pass


class StorerLogger(Logger):

    def log_start_process(self, date: int) -> None:
        print(f"Storing year - {date}")


    def log_end_process(self,  date: int) -> None:
        print(f"Year stored - {date}")


class ImporterLogger(Logger):

    def log_start_process(self,  date: int) -> None:
        print(f"Importing year - {date}")


    def log_end_process(self, date: int) -> None:
        print(f"Year imported - {date}")


class BuilderLogger(Logger):

    def log_start_process(self, date: int) -> None:
        print(f"Building month - {date}")


    def log_end_process(self, date: int) -> None:
        print(f"Month builded - {date}")



class NullLogger(Logger):
    def log_start_process(self, date: int) -> None:
        pass


    def log_end_process(self, date: int) -> None:
        pass
