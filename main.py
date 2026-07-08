from fastapi import FastAPI
from backend.routers import dengue_router

app = FastAPI(
    title="Dengue Data Engine",
    description=(
        "A data engine and REST API designed to ingest, organize, store, "
        "and distribute official dengue epidemiological data from the "
        "Brazilian Ministry of Health Open Data Portal (SINAN/Dengue)."
    ),
    version="1.0.0",
)

app.include_router(
    dengue_router.router,
    prefix="/api/dengue",
    tags=["Arbovirus - Dengue"])


