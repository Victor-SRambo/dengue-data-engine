

from fastapi import FastAPI
from backend.routers import dengue_router
from backend.services import factory


app = FastAPI()

app.include_router(
    dengue_router.router,
    prefix="/api/dengue",
    tags=["Arbovirus - Dengue"])



dataset_builder = factory.create_dengue_dataset_builder()
dataset_storer = factory.create_dengue_dataset_storer()
dataset_importer = factory.create_dengue_dataset_importer()
dataset_searcher = factory.create_dengue_dataset_searcher()
dataset_forecaster = factory.create_dengue_dataset_forecaster()

dataset_importer.import_years(20241201, 20261201)
dataset_storer.store_years(20241201, 20261201)
dataset_builder.build_years(20241201, 20261201)

cases = dataset_searcher.get_cases_dates(20240107, 20260708, 431140)
cases = dataset_searcher.get_num_cases_dates(20240107, 20260708, 431140)
date_to_forecast = dataset_forecaster.get_dengue_forecast(431140)

print(cases)
print(date_to_forecast)