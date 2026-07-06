from fastapi import APIRouter, HTTPException
from typing import List
from pydantic import BaseModel
from backend.services import factory

router = APIRouter()

class DengueCaseResponse(BaseModel):
    notification_date: int
    city_notification_code: int
    
    class Config:
        from_attributes = True


@router.get("/cases", response_model=List[DengueCaseResponse])
def get_cases(city_code: int, start_date: int, end_date: int):

    dataset_searcher = factory.create_dengue_dataset_searcher()
    cases = dataset_searcher.get_cases_dates(start_date, end_date, city_code)

    if not cases:
        raise HTTPException(status_code=404, detail="No cases found")

    return cases
