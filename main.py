

from build.Debug import dengue
from backend.services import importer, loader, normalizer
from fastapi import FastAPI
import polars as pl

app = FastAPI()

@app.get("/pedroammes")
def root(nome: str):
    return {"Hello": f"{nome}"}




loader = loader.DadosAbertosLoader()
importer = importer.DadosAbertosImporter()
file_manager = dengue.FileManager()
file_manager.truncate_bins(2026)

for df_bath in loader.map_cases(26):

    ages = df_bath["NU_IDADE_N"].to_list()
    notification_date = df_bath["DT_NOTIFIC"].to_list()
    first_symptoms_date = df_bath["DT_SIN_PRI"].to_list()
    city_notification_code = df_bath["ID_MUNICIP"].to_list()

    mapper = dengue.DadosAbertosMapper()
    dengue_cases = mapper.mapDengueCase(ages, 
                                        notification_date, 
                                        first_symptoms_date, 
                                        city_notification_code)

    file_manager.append_bin(dengue_cases)

data = file_manager.load_bin(20262)
sorter = dengue.CaseSorter()
sorted_indexes = sorter.sort(data)
sorted_data = [data[i] for i in sorted_indexes]

for case in sorted_data:
    print(case.city_notification_code)


#funções:
#carrega csv na db