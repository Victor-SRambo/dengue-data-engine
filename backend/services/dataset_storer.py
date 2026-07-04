from backend.services import csv_loader, csv_normalizer, csv_list_converter
from build.Debug import dengue
from abc import ABC, abstractmethod
from datetime import datetime
from dateutil.relativedelta import relativedelta


class ArbovirusDataStorer(ABC):

    @abstractmethod
    def store_years(self, start_year, end_year):
        pass   

    @abstractmethod
    def store_year(self, year):
        pass   




class DengueDataStorer(ArbovirusDataStorer):

    def store_years(self, start_year, end_year):
        y_current= datetime.strptime(str(start_year), "%Y")
        end_year = datetime.strptime(str(end_year), "%Y")

        while y_current <= end_year:
            year = y_current.strftime("%Y")
            self.store_year(year)

            y_current = y_current + relativedelta(years=1)


    def store_year(self, year):
        loader = csv_loader.DengueLoader(csv_normalizer.DengueNormalizer())
        list_converter = csv_list_converter.DengueListConverter()

        mapper = dengue.DadosAbertosMapper()
        file_manager = dengue.FileManager()

        file_manager.truncate_bins(int(year))

        for df_batch in loader.batch_load_csv(year):
                fields = list_converter.to_list(df_batch)
                dengue_cases = mapper.mapDengueCase(fields)
                file_manager.append_bin(dengue_cases, int(year))


