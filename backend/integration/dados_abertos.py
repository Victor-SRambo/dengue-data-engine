import requests
import zipfile


def requestZipCasesYear(year : int):
    url = f"https://s3.sa-east-1.amazonaws.com/ckan.saude.gov.br/SINAN/Dengue/csv/DENGBR{year}.csv.zip"
    mb = 100 *1024 *1024 # 100 mb

    response = requests.get(url) 

    with open("backend/data/temp.zip","wb") as file:
        for chunk in response.iter_content(chunk_size=mb):
            file.write(chunk)


def unzipCasesYear(year : int, delete : bool = True):
    with zipfile.ZipFile("backend/data/temp.zip","r") as file:
        file.extractall("backend/data")
