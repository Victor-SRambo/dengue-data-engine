from abc import ABC, abstractmethod


class CaseMapper(ABC):

    @abstractmethod
    def map_cases(self):
        pass


class DadosAbertosMapper(CaseMapper):

    def map_cases(self):
        print("Hello")

