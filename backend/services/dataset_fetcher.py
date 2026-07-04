from abc import ABC, abstractmethod
from datetime import datetime
from build.Debug import dengue
from dateutil.relativedelta import relativedelta


class ArbovirusDataFetcher(ABC):

    @abstractmethod
    def fetch_dates(self, city_code, start_date, end_date):
        pass   


    @abstractmethod
    def fetch_months(self, city_code, start_date, end_date):
        pass   


class DengueDataFetcher(ArbovirusDataFetcher):

    def fetch_dates(self, city_code, start_date, end_date):
        pass


    def fetch_months(self, city_code, start_date, end_date):
        pass