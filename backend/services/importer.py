from backend.integration import dados_abertos
from abc import ABC, abstractmethod


#MUDAR NOME CSV_fetcher

class ArbovirusImporter(ABC):

    @abstractmethod
    def import_year(self, year):
        pass



class DengueImporter(ArbovirusImporter):

    def import_year(self, year):
        print("Começando importação")
        dados_abertos.requestCSVCasesYear(year)
        print("Importação concluida com sucesso")

