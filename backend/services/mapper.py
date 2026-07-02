from abc import ABC, abstractmethod
import csv
from build.Debug import dengue

from backend.services import normalizer



class CaseMapper(ABC):

    @abstractmethod
    def map_cases(self, year):
        pass


class DadosAbertosMapper(CaseMapper):

    def __init__(self):
        self.normalizer = normalizer.DadosAbertosNormalizer()

    def map_cases(self, year):
        print("Começando mapeamento")

        with open(f"backend/data/DENGBR{year}.csv", "r", buffering=10485760) as file:
            reader = csv.reader(file)
            headers = next(reader)
            
            # Map header names to their column index numbers
            idx_age = headers.index("NU_IDADE_N")
            idx_birth = headers.index("ANO_NASC")

            case = dengue.DengueCase()

            norm_age = self.normalizer.age
            norm_year = self.normalizer.year_birth
            
            for row in reader:
                case.age = norm_age(row[idx_age])
                case.year_birth = norm_year(row[idx_birth])

                yield case

        print("Mapeamente concluido com sucesso")
                

