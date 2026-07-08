from abc import ABC, abstractmethod
from build.Debug import engine, dengue
from backend.services.utils import date_utils


class ArbovirusDataBuilder(ABC):

    @abstractmethod
    def build_years(self, start_date_ym: int, end_date_ym: int) -> None:
        pass   



class DengueDataBuilder(ArbovirusDataBuilder):

    def __init__(self, file_manager, sorter, indexer, logger):
        self.file_manager = file_manager
        self.sorter = sorter
        self.indexer = indexer
        self.logger = logger


    def build_years(self, start_date_ym: int, end_date_ym: int) -> None:
        for date_ym in date_utils.get_all_months_int(start_date_ym, end_date_ym):
            self._build_month(date_ym)


    def _build_month(self, date_ym: int) -> None:
        self.logger.log_start_process(date_ym)

        cases = self.file_manager.load_cases_date_bin(date_ym)
        if not cases: 
            return

        sorted_cases_by_city = [cases[i] for i in self.sorter.sort(cases, engine.DengueCityCodeField())]
        city_indexes = self.indexer.create_city_indexes(sorted_cases_by_city)

        sorted_cases_by_city_date = self._sort_cases_by_date_per_city(sorted_cases_by_city, city_indexes)

        self.file_manager.overwrite_cases_bin(sorted_cases_by_city_date, date_ym)
        self.file_manager.overwrite_city_indexes(city_indexes, date_ym)

        self.logger.log_end_process(date_ym)


    def _sort_cases_by_date_per_city(self, sorted_cases_by_city: list, city_indexes: int) -> list:
        sorted_cases = []
        
        for index in city_indexes:
            city_cases = sorted_cases_by_city[index.start:index.end]
            sorted_city_cases = [city_cases[i] for i in self.sorter.sort(city_cases, engine.DengueDateField())]
            sorted_cases.extend(sorted_city_cases)

        return sorted_cases