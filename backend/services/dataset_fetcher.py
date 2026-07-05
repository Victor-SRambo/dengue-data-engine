from abc import ABC, abstractmethod
from datetime import datetime
from build.Debug import dengue
from dateutil.relativedelta import relativedelta


class ArbovirusDataFetcher(ABC):

    @abstractmethod
    def fetch_dates(self, city_code, start_date, end_date):
        pass   

    @abstractmethod
    def fetch_entire_month(self, city_code, date):
        pass   

    @abstractmethod
    def fetch_month_after_date(self, city_code, date):
        pass

    @abstractmethod
    def fetch_month_before_date(self, city_code, date):
        pass


class DengueDataFetcher(ArbovirusDataFetcher):

    def fetch_dates(self, city_code, start_date, end_date):

        current_date = datetime.strptime(str(start_date), "%Y%m%d")
        end_date = datetime.strptime(str(end_date), "%Y%m%d")


        delta = relativedelta(current_date, end_date)
        month_delta = 12 * delta.years + delta.months

        current_dateYMD = current_date.strftime("%Y%m%d")
        end_dateYMD = end_date.strftime("%Y%m%d")

        if month_delta == 0:
            cases = self.fetch_entire_month(city_code, current_dateYMD)
            return cases
        
        if month_delta == 1:
            cases = self.fetch_entire_month(city_code, current_dateYMD) + self.fetch_entire_month(city_code, end_dateYMD)
            return cases
        
        cases = []
        
        cases.extend(self.fetch_month_after_date(city_code, current_dateYMD))
        end_date = end_date - relativedelta(months=1)

        while current_date < end_date :
            current_date = current_date + relativedelta(months=1)

            current_dateYMD = current_date.strftime("%Y%m%d")
            cases.extend(self.fetch_entire_month(city_code, current_dateYMD))

        current_date = current_date + relativedelta(months=1)
        current_dateYMD = current_date.strftime("%Y%m%d")
        cases.extend(self.fetch_month_before_date(city_code, current_dateYMD))

        return cases

    def fetch_month_after_date(self, city_code, date):
        file_manager = dengue.FileManager()
        searcher = dengue.BinarySearch()


        date = datetime.strptime(str(date), "%Y%m%d")
        dateYM = date.strftime("%Y%m")
        dateYMD = date.strftime("%Y%m%d")


        indexes = file_manager.load_indexes(int(dateYM))
        index = searcher.index_search(indexes, city_code)

        if not index: return

        cases = file_manager.load_bin_from_index(int(dateYM), index)

        index = searcher.after_date_search(cases, int(dateYMD))

        cases = cases[index::]

        for case in cases[::3]:
            print(f"City Code:{case.city_notification_code} - Date:{case.notification_date}")

        return cases



    def fetch_month_before_date(self, city_code, date):
        file_manager = dengue.FileManager()
        searcher = dengue.BinarySearch()


        date = datetime.strptime(str(date), "%Y%m%d")
        dateYM = date.strftime("%Y%m")
        dateYMD = date.strftime("%Y%m%d")


        indexes = file_manager.load_indexes(int(dateYM))
        index = searcher.index_search(indexes, city_code)

        if not index: return

        cases = file_manager.load_bin_from_index(int(dateYM), index)

        index = searcher.before_date_search(cases, int(dateYMD))


        cases = cases[:index+1]
        for case in cases[::3]:
            print(f"City Code:{case.city_notification_code} - Date:{case.notification_date}")
        return cases



    def fetch_entire_month(self, city_code, date):
        file_manager = dengue.FileManager()
        searcher = dengue.BinarySearch()

        date = datetime.strptime(str(date), "%Y%m%d")
        date = date.strftime("%Y%m")


        indexes = file_manager.load_indexes(int(date))


        index = searcher.index_search(indexes, city_code)

        if not index: return

        cases = file_manager.load_bin_from_index(int(date), index)

        for case in cases[::3]:
            print(f"City Code:{case.city_notification_code} - Date:{case.notification_date}")

        return cases
        



