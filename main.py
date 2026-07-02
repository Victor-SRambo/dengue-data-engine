

from build.Debug import dengue
from backend.services import importer, mapper, normalizer
from fastapi import FastAPI

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



mapper = mapper.DadosAbertosMapper()
importer = importer.DadosAbertosImporter()

importer.import_year(24)

for case in mapper.map_cases(24):
    pass

#funções:
#carrega csv na db