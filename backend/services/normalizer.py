from abc import ABC, abstractmethod
import polars as pl


class CaseNormalizer(ABC):

    @abstractmethod
    def age(self, age):
        pass


class DadosAbertosNormalizer():

    def normalize_date(self, df, column):
        return df.with_columns(
            pl.col(f"{column}")
            .str.replace_all("-", "")
            .cast(pl.Int64, strict=False)
            .fill_null(0)
            .alias(f"{column}")
        )
    
    def normalize_int(self, df, column):
        return df.with_columns(
            pl.col(f"{column}")
            .cast(pl.Int64, strict=False)
            .fill_null(0)
            .alias(f"{column}")
        )



#vai precisar fazer do ano de nascimento