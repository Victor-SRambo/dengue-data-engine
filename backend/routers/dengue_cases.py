from fastapi import APIRouter, Query
from typing import List, Dict
from pydantic import BaseModel, Field
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

    class Config:
        from_attributes = True



_page_max_size = 500

@router.get("/cases-city-date", response_model=List[DengueCaseResponse])
def get_cases(city_code: int = Query(description="**Filter**: Brasilian City of Occurrence \n\n - **Format** Six first digits of IBGE city code identifier"), 
              start_date: int = Query(description="**Filter**: Start Date \n\n - **Format**: `YYYYMMDD`"), 
              end_date: int = Query(description="Filter: End Date \n\n - **Format**: `YYYYMMDD`"),
              page: int = 1,
              page_size: int = _page_max_size):
    
    page_size = min(page_size, _page_max_size)
    offset = (page - 1) * page_size

    dataset_searcher = factory.create_dengue_dataset_searcher()
    cases = dataset_searcher.get_cases_dates(start_date, end_date, city_code)

    if not cases:
        return []

    response = cases[offset:offset+page_size]

    return response



@router.get("/num-cases-city-date", response_model=List[DengueNumCasesResponse])
def get_cases(city_code: int = Query(description="**Filter**: Brasilian City of Occurrence \n\n - **Format** Six first digits of IBGE city code identifier"), 
              start_date: int = Query(description="**Filter**: Start Date \n\n - **Format**: `YYYYMMDD`"), 
              end_date: int = Query(description="Filter: End Date \n\n - **Format**: `YYYYMMDD`")):
    


    dataset_searcher = factory.create_dengue_dataset_searcher()
    cases = dataset_searcher.get_num_cases_dates(start_date, end_date, city_code)

    if not cases:
        return []
    
    response = []
    for date, num_cases in cases.items():
        response.append(DengueNumCasesResponse(date_ym=date, num_cases=num_cases))


    return response