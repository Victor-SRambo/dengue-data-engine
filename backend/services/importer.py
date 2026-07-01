from backend.integration import dados_abertos
from abc import ABC, abstractmethod




class CaseImporter(ABC):

    @abstractmethod
    def import_year(self):
        pass



class DadosAbertosImporter(CaseImporter):

    def import_year(self, year):
        dados_abertos.requestZipCasesYear(year)
        dados_abertos.unzipCasesYear(year)

