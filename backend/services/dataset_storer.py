
from abc import ABC, abstractmethod
from backend.services.utils import date_utils


class ArbovirusDataStorer(ABC):

    @abstractmethod
    def store_years(self, start_year, end_year):
        pass   

    @abstractmethod
    def store_year(self, year):
        pass   


class DengueDataStorer(ArbovirusDataStorer):

    def __init__(self, loader, list_converter, mapper, file_manager):
         self.loader = loader
         self.list_converter = list_converter
         self.mapper = mapper
         self.file_manager = file_manager


    def store_years(self, start_year, end_year):
        start_year = date_utils.convert_to_datetime(start_year)
        end_year = date_utils.convert_to_datetime(end_year)

        for year in date_utils.get_all_years_datetime(start_year, end_year):
            self.store_year(year)


    def store_year(self, year):
        year = date_utils.date_to_int_y_full(year)
        self.file_manager.truncate_cases_year_bin(year)

        for df_batch in self.loader.batch_load_csv(year):
                
                if df_batch is None: 
                     continue

                fields = self.list_converter.to_list(df_batch)
                cases = self.mapper.map_vectors_to_class(fields)
                self.file_manager.append_cases_year_bin(cases, year)


