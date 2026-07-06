

from backend.services import factory
from fastapi import FastAPI

app = FastAPI()

@app.get("/pedroammes")
def root(nome: str):
    return {"Hello": f"{nome}"}


dataset_importer = factory.create_dengue_dataset_importer()
dataset_importer.import_years(2026, 2027)

dataset_storer = factory.create_dengue_dataset_storer()
dataset_storer.store_years(2026, 2027)

dataset_builder = factory.create_dengue_dataset_builder()
dataset_builder.build_years(2026, 2027)

dataset_searcher = factory.create_dengue_dataset_searcher()
cases = dataset_searcher.get_cases_dates(20260501, 20260615, 320530)

for case in cases:
    print(case.notification_date)