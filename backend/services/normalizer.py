from abc import ABC, abstractmethod
import polars as pl


class CaseNormalizer(ABC):

    @abstractmethod
    def age(self, age):
        pass


class DadosAbertosNormalizer():

    def normalize_date(self, df, column):
        df = df.with_columns(
            pl.col(f"{column}")
            .str.replace_all("-", "")
            .cast(pl.Int64, strict=False)
            .alias(f"{column}")
        )

        return df.filter(
            (pl.col(column).is_not_null()) & (pl.col(column) != 0),
        )
    
    def normalize_int(self, df, column):
        return df.with_columns(
            pl.col(f"{column}")
            .cast(pl.Int64, strict=False)
            .fill_null(0)
            .alias(f"{column}")
        )



#vai precisar fazer do ano de nascimento