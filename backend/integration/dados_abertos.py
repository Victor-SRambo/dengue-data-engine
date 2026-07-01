import requests
import zipfile


#MUDAR ANO PARA ACEITAR 4 DIGITOS



def fectchReportYear(ano : int):

    url = f"https://s3.sa-east-1.amazonaws.com/ckan.saude.gov.br/SINAN/Dengue/csv/DENGBR{ano}.csv.zip"
    mb = 100 *1024 *1024 # 100 mb

    response = requests.get(url) 


    with open("backend/data/temp.zip","wb") as file:
        for chunk in response.iter_content(chunk_size=mb):
            file.write(chunk)

    with zipfile.ZipFile("backend/data/temp.zip","r") as file:
        file.extractall("backend/data")



fectchReportYear(26)