from abc import ABC, abstractmethod
from backend.services.utils import date_utils
from build.Debug import dengue


class ArbovirusDataSearcher(ABC):

    @abstractmethod
    def get_cases_dates(self, start_date, end_date, city_code):
        pass   



class DengueDataSearcher(ArbovirusDataSearcher):

    def __init__(self, file_manager, binary_searcher):
        self.file_manager = file_manager
        self.binary_searcher = binary_searcher

    def get_cases_dates(self, start_date, end_date, city_code):

        start_date = date_utils.convert_to_datetime(start_date)
        end_date = date_utils.convert_to_datetime(end_date)
        cases = []

        month_diference = end_date.month - start_date.month

        if month_diference == 0:
            before_cases_dates = {c.notification_date for c in self._get_cases_before_date_in_month(end_date, city_code)}

            for case in self._get_cases_after_date_in_month(start_date, city_code):                    
                if case.notification_date in before_cases_dates:
                    cases.append(case)
            
        
        elif month_diference == 1:
            cases.extend(self._get_cases_after_date_in_month(start_date, city_code))
            cases.extend(self._get_cases_before_date_in_month(end_date, city_code))

        else:
            cases.extend(self._get_cases_after_date_in_month(start_date, city_code))

            for date in date_utils.get_intermediate_months_datetime(start_date, end_date) :
                cases.extend(self._get_cases_entire_month(date, city_code))
                
            cases.extend(self._get_cases_before_date_in_month(end_date, city_code))

        return cases
    

    def _get_city_index(self, date, city_code):
        date = date_utils.date_to_int_ym(date)

        indexes = self.file_manager.load_indexes(date)
        index = self.binary_searcher.index_search(indexes, city_code)

        return index
    

    def _get_cases_from_index(self, date, index):
        date_ym = date_utils.date_to_int_ym(date)
        return self.file_manager.load_bin_from_index(date_ym, index)
    

    def _get_cases_after_date_in_month(self, date, city_code):
        index = self._get_city_index(date, city_code)
        if index is None: return []

        cases = self._get_cases_from_index(date, index)

        date_ymd = date_utils.date_to_int_ymd(date)
        first_case = self.binary_searcher.after_date_search(cases, date_ymd)
        return cases[first_case::]

    def _get_cases_before_date_in_month(self, date, city_code):
        index = self._get_city_index(date, city_code)
        if index is None: return []

        cases = self._get_cases_from_index(date, index)

        date_ymd = date_utils.date_to_int_ymd(date)
        last_case = self.binary_searcher.before_date_search(cases, date_ymd)

        return cases[:last_case+1]


    def _get_cases_entire_month(self, date, city_code):
        index = self._get_city_index(date, city_code)
        if index is None: return []

        return self._get_cases_from_index(date, index)

        

