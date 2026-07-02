from abc import ABC, abstractmethod
import math


class CaseNormalizer(ABC):

    @abstractmethod
    def age(self, age):
        pass


class DadosAbertosNormalizer():

    def age(self, age):
        age = int(age)
        age = math.ceil(age / 100)
        return age
    

    def year_birth(self, year):

        if not year:
            return 0

        year = int(year)
        return year
