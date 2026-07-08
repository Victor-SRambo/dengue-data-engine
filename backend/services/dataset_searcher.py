from abc import ABC, abstractmethod
from backend.services.utils import date_utils
from datetime import datetime
from build.Debug.dengue import DengueCase
from build.Debug.engine import IndexRegister


class ArbovirusDataSearcher(ABC):

    @abstractmethod
    def get_cases_dates(self, start_date: int, end_date: int, city_code: int) -> list[DengueCase]:
        pass   

    @abstractmethod
    def get_num_cases_dates(self, start_date: int, end_date: int, city_code: int) -> dict:
        pass   


class DengueDataSearcher(ArbovirusDataSearcher):

    def __init__(self, file_manager, binary_searcher):
        self.file_manager = file_manager
        self.binary_searcher = binary_searcher

    def get_cases_dates(self, start_date: int, end_date: int, city_code: int) -> list[DengueCase]:

        start_date = date_utils.convert_to_datetime(start_date)
        end_date = date_utils.convert_to_datetime(end_date)
        cases = []

        month_difference = end_date.month - start_date.month
        print(month_difference)

        if month_difference == 0:
            before_cases_dates = {c.notification_date for c in self._get_cases_before_date_in_month(end_date, city_code)}

            for case in self._get_cases_after_date_in_month(start_date, city_code):                    
                if case.notification_date in before_cases_dates:
                    cases.append(case)
            
        elif month_difference == 1:
            cases.extend(self._get_cases_after_date_in_month(start_date, city_code))
            cases.extend(self._get_cases_before_date_in_month(end_date, city_code))

        else:
            cases.extend(self._get_cases_after_date_in_month(start_date, city_code))

            for date in date_utils.get_intermediate_months_datetime(start_date, end_date) :
                cases.extend(self._get_cases_entire_month(date, city_code))
                
            cases.extend(self._get_cases_before_date_in_month(end_date, city_code))


        return cases
    

    def get_num_cases_dates(self, start_date: int, end_date: int, city_code: int) -> dict:
        start_date = date_utils.convert_to_datetime(start_date)
        end_date = date_utils.convert_to_datetime(end_date)

        month_num_cases = {}

        for date in date_utils.get_all_months_datetime(start_date, end_date):

            date_ym = date_utils.date_to_int_ym(date)
            index = self._get_city_index(date, city_code)

            if index is None: 
                month_num_cases[date_ym] = 0
                continue

            num_cases = index.end - index.start
            month_num_cases[date_ym] = num_cases

        return month_num_cases
    

    def _get_city_index(self, date: datetime, city_code: int) -> IndexRegister:
        date = date_utils.date_to_int_ym(date)

        indexes = self.file_manager.load_city_indexes(date)
        if indexes is None: return None

        index = self.binary_searcher.index_search(indexes, city_code)
        if index is None: return None

        return index
    

    def _get_cases_from_city(self, date: datetime, city_code: int) -> list[DengueCase]:
        index = self._get_city_index(date, city_code)
        if index is None: return None

        date_ym = date_utils.date_to_int_ym(date)
        cases = self.file_manager.load_cases_from_index_bin(date_ym, index)
        if cases is None: return None

        return cases

    def _get_cases_after_date_in_month(self, date: datetime, city_code: int) -> list[DengueCase]:
        cases = self._get_cases_from_city(date, city_code)
        if cases is None: return []

        date_ymd = date_utils.date_to_int_ymd(date)
        first_case = self.binary_searcher.after_date_search(cases, date_ymd)
        return cases[first_case::]

    def _get_cases_before_date_in_month(self, date: datetime, city_code: int) -> list[DengueCase]:
        cases = self._get_cases_from_city(date, city_code)
        if cases is None: return []

        date_ymd = date_utils.date_to_int_ymd(date)
        last_case = self.binary_searcher.before_date_search(cases, date_ymd)

        return cases[:last_case+1]


    def _get_cases_entire_month(self, date: datetime, city_code: int) -> list[DengueCase]:
        cases = self._get_cases_from_city(date, city_code)
        if cases is None: return []
    
        return cases

        

