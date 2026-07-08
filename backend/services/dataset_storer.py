
from abc import ABC, abstractmethod
from backend.services.utils import date_utils
from datetime import datetime


class ArbovirusDataStorer(ABC):

    @abstractmethod
    def store_years(self, start_year, end_year):
        pass   

    @abstractmethod
    def store_year(self, year):
        pass   


class DengueDataStorer(ArbovirusDataStorer):

    def __init__(self, loader, normalizer, list_converter, mapper, file_manager, logger):
        self.logger = logger
        self.loader = loader
        self.normalizer = normalizer
        self.list_converter = list_converter
        self.mapper = mapper
        self.file_manager = file_manager


    def store_years(self, start_year: int, end_year: int) -> None:
        for year in date_utils.get_all_years_int(start_year, end_year):
            self.store_year(year)



    def store_year(self, year: int) -> None:
        self.logger.log_start_process(year)

        self.file_manager.truncate_cases_year_bin(year)

        for df_batch in self.loader.batch_load_csv(year):
            if df_batch is None: 
                    continue

            df_batch = self.normalizer.normalize_cases_csv(df_batch)
            fields = self.list_converter.to_list(df_batch)
            cases = self.mapper.map_vectors_to_class(fields)
            self.file_manager.append_cases_year_bin(cases, year)

        self.logger.log_end_process(year)


