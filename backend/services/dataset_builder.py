from abc import ABC, abstractmethod
from build.Debug import case_sorter
from backend.services.utils import date_utils


class ArbovirusDataBuilder(ABC):

    @abstractmethod
    def build_years(self, start_year, end_year):
        pass   



class DengueDataBuilder(ArbovirusDataBuilder):

    def __init__(self, file_manager, sorter, indexer):
        self.file_manager = file_manager
        self.sorter = sorter
        self.indexer = indexer


    def build_years(self, start_year, end_year):
        start_year = date_utils.convert_to_datetime(start_year)
        end_year = date_utils.convert_to_datetime(end_year)

        for date in date_utils.get_all_months_datetime(start_year, end_year):
            self._build_month(date)


    def _build_month(self, date):
        date = date_utils.date_to_int_ym(date)

        cases = self.file_manager.load_bin(date)
        if not cases: return

        sorted_cases_by_city = [cases[i] for i in self.sorter.sort(cases, case_sorter.CityCodeField())]
        city_indexes = self.indexer.create_index(sorted_cases_by_city)
        sorted_cases_by_city_date = self._sort_cases_by_date_per_city(sorted_cases_by_city, city_indexes)

        self.file_manager.overwrite_bin(sorted_cases_by_city_date, date)
        self.file_manager.save_indexes(city_indexes, date)

        print("Month Done!!!")


    def _sort_cases_by_date_per_city(self, sorted_cases_by_city, city_indexes):
        sorted_cases = []
        for index in city_indexes:
            city_cases = sorted_cases_by_city[index.start:index.end]
            sorted_city_cases = [city_cases[i] for i in self.sorter.sort(city_cases, case_sorter.DateField())]
            sorted_cases.extend(sorted_city_cases)

        return sorted_cases