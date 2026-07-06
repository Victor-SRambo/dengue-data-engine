

from backend.services import factory
from fastapi import FastAPI
from backend.routers import dengue_cases

app = FastAPI()

app.include_router(dengue_cases.router)



"""dataset_importer = factory.create_dengue_dataset_importer()
dataset_importer.import_years(20260101, 20261201)

dataset_storer = factory.create_dengue_dataset_storer()
dataset_storer.store_years(20260101, 20261201)


dataset_builder = factory.create_dengue_dataset_builder()
dataset_builder.build_years(20260101, 20261201)

dataset_searcher = factory.create_dengue_dataset_searcher()
cases = dataset_searcher.get_cases_dates(20260417, 20260615, 320530)

for case in cases:
    print(case.notification_date)"""