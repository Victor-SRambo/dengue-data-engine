from abc import ABC, abstractmethod
from datetime import datetime
from dateutil.relativedelta import relativedelta

class ArbovirusDataImporter(ABC):

    @abstractmethod
    def import_years(self, year):
        pass   


    @abstractmethod
    def import_year(self, start_year, end_year):
        pass   


class DengueDataImporter(ArbovirusDataImporter):

    def __init__(self, client):
        self.client = client



    def import_years(self, start_year, end_year):
        y_current= datetime.strptime(str(start_year), "%Y")
        end_year = datetime.strptime(str(end_year), "%Y")

        while y_current <= end_year:
            year = y_current.strftime("%y")
            self.import_year(year)

            y_current = y_current + relativedelta(years=1)


    def import_year(self, year):
        print(f"Importing year: {year}")
        self.client.request_year_csv(year)