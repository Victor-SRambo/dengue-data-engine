from abc import ABC, abstractmethod
import requests
import zipfile
import os



class ArbovirusHttpClient(ABC):

    @abstractmethod
    def request_year_csv(self, year: int) -> None:
        pass


class DengueHttpClient(ArbovirusHttpClient):

    def request_year_csv(self, year: int) -> None:

        year_short = year % 100  # Date Format: YYYY -> YY
        url = f"https://s3.sa-east-1.amazonaws.com/ckan.saude.gov.br/SINAN/Dengue/csv/DENGBR{year_short}.csv.zip"
        mb = 100 *1024 *1024 # 100 mb

        response = requests.get(url, stream=True) 

        if response.status_code != 200: 
            print("Error doing request of resource")
            return None
        

        with open("backend/data/temp.zip","wb") as file:
            for chunk in response.iter_content(chunk_size=mb):
                file.write(chunk)

        with zipfile.ZipFile("backend/data/temp.zip","r") as file:
            file.extractall("backend/data")

        os.replace(f"backend/data/DENGBR{year_short}.csv", f"backend/data/DENGBR{year}.csv")
        os.remove(f"backend/data/temp.zip")