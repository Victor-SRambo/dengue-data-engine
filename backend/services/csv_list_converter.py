from abc import ABC, abstractmethod
from build.Debug import dengue


class ArbovirusListConverter(ABC):

    @abstractmethod
    def to_list(self, df):
        pass


class DengueListConverter(ArbovirusListConverter):

    def to_list(self, df):
        fields = dengue.DengueFieldVectors()

        fields.notification_dates = df["DT_NOTIFIC"].to_list()
        fields.first_symptoms_dates = df["DT_SIN_PRI"].to_list()
        fields.epidemiological_weeks = df["SEM_NOT"].to_list()
        fields.state_notification_codes = df["SG_UF_NOT"].to_list()
        fields.city_notification_codes = df["ID_MUNICIP"].to_list()
        fields.state_living_codes = df["SG_UF"].to_list()
        fields.city_living_codes = df["ID_MN_RESI"].to_list()
        fields.ages = df["NU_IDADE_N"].to_list()
        fields.year_births = df["ANO_NASC"].to_list()
        fields.escolarities = df["CS_ESCOL_N"].to_list()
        fields.professions = df["ID_OCUPA_N"].to_list()
        fields.pregnancy_states = df["CS_GESTANT"].to_list()
        fields.ethnicities = df["CS_RACA"].to_list()
        fields.sexes = df["CS_SEXO"].to_list()

        return fields
    
