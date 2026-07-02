from abc import ABC, abstractmethod
from backend.services import normalizer
import polars as pl


COLUMNS = [
    "DT_NOTIFIC", "DT_SIN_PRI", "SEM_NOT",
    "SG_UF_NOT", "ID_MUNICIP",
    "SG_UF", "ID_MN_RESI",
    "NU_IDADE_N", "ANO_NASC",
    "CS_ESCOL_N", "ID_OCUPA_N", "CS_GESTANT",
    "CS_RACA", "CS_SEXO",
]


class CaseLoader(ABC):

    @abstractmethod
    def map_cases(self, year):
        pass


class DadosAbertosLoader(CaseLoader):

    def __init__(self):
        self.normalizer = normalizer.DadosAbertosNormalizer()

    def map_cases(self, year):
        print("Começando mapeamento")


        lf = pl.scan_csv(f"backend/data/DENGBR{year}.csv", ignore_errors=True).select(COLUMNS);

        for df_batch in lf.collect_batches(chunk_size=20000):

            df_batch = self.normalizer.normalize_date(df_batch, "DT_NOTIFIC")
            df_batch = self.normalizer.normalize_date(df_batch, "DT_SIN_PRI")
            df_batch = self.normalizer.normalize_int(df_batch, "NU_IDADE_N")


            print("Mapeamento concluido com sucesso")

            yield df_batch
            # MUDAR NOME N ESTÁ MAPEANDO MAIS