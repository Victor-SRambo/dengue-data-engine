from abc import ABC, abstractmethod
from datetime import datetime
from build.Debug import dengue
from dateutil.relativedelta import relativedelta


class ArbovirusDataBuilder(ABC):

    @abstractmethod
    def build_years(self, year):
        pass   


    @abstractmethod
    def build_month(self, date):
        pass   


class DengueDataBuilder(ArbovirusDataBuilder):

    def build_years(self, start_year, end_year):
        y_current= datetime.strptime(str(start_year), "%Y")
        end_year = datetime.strptime(str(end_year), "%Y")

        while y_current <= end_year:

            for _ in range(13):

                year = y_current.strftime("%Y%m")
                self.build_month(year)
                y_current = y_current + relativedelta(months=1)
            
            y_current = y_current + relativedelta(years=1)


    def build_month(self, date):
        file_manager = dengue.FileManager()
        sorter = dengue.CaseSorter()
        indexer = dengue.Indexer()
        sorter.select_field(dengue.CaseCityCodeField())


        data = file_manager.load_bin(int(date))

        if not data: return

        sorted_indexes = sorter.sort(data)
        sorted_data = [data[i] for i in sorted_indexes]

        indexes = indexer.create_index(sorted_data)

        sorter.select_field(dengue.CaseDateField())

        final_sorted = []

        for index in indexes:
            chunk = sorted_data[index.start:index.end]

            idx = sorter.sort(chunk)
            sorted_chunk = [chunk[i] for i in idx]

            final_sorted.extend(sorted_chunk)

        file_manager.overwrite_bin(final_sorted, int(date))


        print("Month Done!!!")