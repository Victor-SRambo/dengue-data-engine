from abc import ABC, abstractmethod
from backend.services.utils import date_utils
from datetime import datetime


class ArbovirusDataImporter(ABC):

    @abstractmethod
    def import_years(self, year):
        pass   


    @abstractmethod
    def import_year(self, start_year, end_year):
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