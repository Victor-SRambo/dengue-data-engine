from fastapi import FastAPI
from backend.routers import dengue_router

app = FastAPI()

app.include_router(
    dengue_router.router,
    prefix="/api/dengue",
    tags=["Arbovirus - Dengue"])


