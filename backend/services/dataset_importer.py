from abc import ABC, abstractmethod
from backend.services.utils import date_utils


class ArbovirusDataImporter(ABC):

    @abstractmethod
    def import_years(self, start_year: int, end_year: int) -> None:
        pass   


    @abstractmethod
    def import_year(self, year: int) -> None:
        pass   


class DengueDataImporter(ArbovirusDataImporter):

    def __init__(self, client, logger):
        self.client = client
        self.logger = logger


    def import_years(self, start_year: int, end_year: int) -> None:
        for year in date_utils.get_all_years_int(start_year, end_year):
            self.import_year(year)


    def import_year(self, year: int) -> None:
        self.logger.log_start_process(year)
        self.client.request_year_csv(year)
        self.logger.log_end_process(year)