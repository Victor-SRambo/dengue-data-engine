from fastapi import APIRouter, Query
from typing import List
from pydantic import BaseModel
from backend.services import factory

router = APIRouter()


class DengueCaseResponse(BaseModel):
    notification_date: int 
    first_symptoms_date: int
    epidemiological_week: int
    
    state_notification_code: int
    city_notification_code: int

    state_living_code: int
    city_living_code: int

    age: int
    year_birth: int
    escolarity: int
    profession: int
    pregnacy_state: int
    ethnicity: int
    sex: str 
    
    class Config:
        from_attributes = True


class DengueNumCasesResponse(BaseModel):
    date_ym: int 
    num_cases: int


_PAGE_MAX_SIZE= 500
_CITY_CODE_DESCRIPTION = "**Filter:** Brazilian City of Occurrence \n- **Format:** `Six first digits of IBGE city code identifier`"
_START_DATE_DESCRIPTION = "**Filter:** Start Date \n - **Format:**: `YYYYMMDD`"
_END_DATE_DESCRIPTION = "**Filter:** End Date \n - **Format:**: `YYYYMMDD`"


@router.get("/cases/city-date", response_model=List[DengueCaseResponse])
def get_cases(city_code: int = Query(description=_CITY_CODE_DESCRIPTION), 
              start_date: int = Query(description=_START_DATE_DESCRIPTION), 
              end_date: int = Query(description=_END_DATE_DESCRIPTION),
              page: int = 1,
              page_size: int = _PAGE_MAX_SIZE):
    
    page_size = min(page_size, _PAGE_MAX_SIZE)
    offset = (page - 1) * page_size

    dataset_searcher = factory.create_dengue_dataset_searcher()
    cases = dataset_searcher.get_cases_dates(start_date, end_date, city_code)

    if not cases:
        return []

    response = cases[offset:offset+page_size]

    return response


@router.get("/cases/forecast", response_model=List[DengueNumCasesResponse])
def get_cases(city_code: int = Query(description=_CITY_CODE_DESCRIPTION)):
    
    dataset_forecaster = factory.create_dengue_dataset_forecaster()
    date_to_forecast = dataset_forecaster.get_dengue_forecast(city_code)
    
    response = []
    for date_ym, num_cases_forecast in date_to_forecast.items():
        response.append(DengueNumCasesResponse(date_ym=date_ym, num_cases=num_cases_forecast))

    return response


@router.get("/num-cases/city-date", response_model=List[DengueNumCasesResponse])
def get_cases(city_code: int = Query(description=_CITY_CODE_DESCRIPTION), 
              start_date: int = Query(description=_START_DATE_DESCRIPTION), 
              end_date: int = Query(description=_END_DATE_DESCRIPTION)):
    
    dataset_searcher = factory.create_dengue_dataset_searcher()
    num_monthly_cases = dataset_searcher.get_num_cases_dates(start_date, end_date, city_code)

    if not num_monthly_cases:
        return []
    
    response = []
    for date, num_cases in num_monthly_cases.items():
        response.append(DengueNumCasesResponse(date_ym=date, num_cases=num_cases))

    return response


