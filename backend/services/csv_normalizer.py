from abc import ABC, abstractmethod
import polars as pl


class ArbovirusNormalizer(ABC):

    @abstractmethod
    def normalize_cases_csv(self, df):
        pass

    @abstractmethod
    def normalize_date(self, df, column):
        pass

    @abstractmethod
    def normalize_int(self, df, column):
        pass

    @abstractmethod
    def normalize_sex(self, df, column):
        pass


class DengueNormalizer(ArbovirusNormalizer):

    def normalize_cases_csv(self, df):
        df = self.normalize_date(df, "DT_NOTIFIC")
        df = self.normalize_date(df, "DT_SIN_PRI")
        df = self.normalize_int(df, "SEM_NOT")
        df = self.normalize_int(df, "SG_UF_NOT")
        df = self.normalize_int(df, "ID_MUNICIP")
        df = self.normalize_int(df, "SG_UF")
        df = self.normalize_int(df, "ID_MN_RESI")
        df = self.normalize_int(df, "NU_IDADE_N")
        df = self.normalize_int(df, "ANO_NASC")
        df = self.normalize_int(df, "CS_ESCOL_N")
        df = self.normalize_int(df, "ID_OCUPA_N")
        df = self.normalize_int(df, "CS_GESTANT")
        df = self.normalize_int(df, "CS_RACA")
        df = self.normalize_sex(df, "CS_SEXO")

        return df
    

    def normalize_date(self, df, column):
        df = df.with_columns(
            pl.col(column)
            .str.replace_all("-", "")
            .cast(pl.Int64, strict=False)
            .alias(column)
        )

        return df.filter(
            (pl.col(column).is_not_null()) & (pl.col(column) != 0),
        )
    

    def normalize_int(self, df, column):
        return df.with_columns(
            pl.col(column)
            .cast(pl.Int64, strict=False)
            .fill_null(0)
            .alias(column)
        )
    

    def normalize_sex(self, df, column):
        return df.with_columns(
            pl.col(column)
            .fill_null("?")
            .alias(column)
        )



