

from build.Debug import dengue
from backend.services import importer, loader, normalizer
from fastapi import FastAPI
import polars as pl

app = FastAPI()

@app.get("/pedroammes")
def root(nome: str):
    return {"Hello": f"{nome}"}



"""
caso1 = dengue.DengueCase()
caso1.age = 3

print(caso1.age)

dengue.printAge(caso1)
"""



loader = loader.DadosAbertosLoader()
importer = importer.DadosAbertosImporter()

#importer.import_year(24)

file_manager = dengue.FileManager()
file_manager.truncate_bins(2026)

for df_bath in loader.map_cases(26):

    ages = df_bath["NU_IDADE_N"].to_list()
    notification_date = df_bath["DT_NOTIFIC"].to_list()
    first_symptoms_date = df_bath["DT_SIN_PRI"].to_list()

    mapper = dengue.DadosAbertosMapper()
    dengue_cases = mapper.mapDengueCase(ages, notification_date, first_symptoms_date)

    print(dengue_cases[0].notification_date)
    file_manager.append_bin(dengue_cases)

data = file_manager.load_bin(20262)
print(data[0].age)


#funções:
#carrega csv na db