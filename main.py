

from build.Debug import dengue
from backend.services import importer, mapper
from fastapi import FastAPI

app = FastAPI()

@app.get("/pedroammes")
def root(nome: str):
    return {"Hello": f"{nome}"}



"""
importer = importer.DadosAbertosImporter()
importer.import_year(26)

mapper = mapper.DadosAbertosMapper()
mapper.map_cases()

"""

caso1 = dengue.DengueCase()
caso1.age = 3

print(caso1.age)

dengue.printAge(caso1)

#funções:
#carrega csv na db