from abc import ABC, abstractmethod
import polars as pl
import os


_COLUMNS = [
    "DT_NOTIFIC", "DT_SIN_PRI", "SEM_NOT",
    "SG_UF_NOT", "ID_MUNICIP",
    "SG_UF", "ID_MN_RESI",
    "NU_IDADE_N", "ANO_NASC",
    "CS_ESCOL_N", "ID_OCUPA_N", "CS_GESTANT",
    "CS_RACA", "CS_SEXO",
]


class ArboVirusLoader(ABC):

    @abstractmethod
    def batch_load_csv(self, year):
        pass


class DengueLoader(ArboVirusLoader):

    def batch_load_csv(self, year):
        folder_path = "backend/data/"
        file_name = f"DENGBR{year}.csv"

        file_path = folder_path + file_name


        if not os.path.isfile(file_path):
            print("Csv file does not exist")
            return None

        lf = pl.scan_csv(file_path, ignore_errors=True).select(_COLUMNS);

        for df_batch in lf.collect_batches(chunk_size=40000):
            yield df_batch



