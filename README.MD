# Dengue Data Engine

A pipeline and REST API for ingesting, organizing, storing, and distributing official dengue epidemiological data from the Brazilian Ministry of Health Open Data Portal (SINAN/Dengue).

The storage core is written in C++, using low-level, optimized, and ordered data structures for efficient reading and writing of records, along with indexes for fast lookups and queries. The Python (FastAPI) backend consumes this core directly through bindings (pybind11), exposing the data through a REST API.


## Architecture

```text
| SINAN/Dengue |    |Colection Pipeline|    |   C++ core   |    |  Fast Api  |
| (open-data)  | -> | (python-scripts) | -> |(order, store,| -> | (REST API) |
|              |    |                  |    |  fetch data) |    |            |
```

- Collection: Python scripts download and normalize the raw data from the Ministry of Health's open data portal.

 - Storage: a C++ module organizes records into low-level, ordered, and optimized data structures, persisted in dedicated binary file(s), and builds indexes on top of them for fast record lookups and queries (e.g. by year, state, or municipality).

- Access: the C++ module is compiled as a Python extension (via pybind11) and imported directly by the backend — there is no intermediate file reading or extra serialization between layers.

- Distribution: the FastAPI application exposes the data via REST endpoints, automatically documented with Swagger.

## Prerequisites

Before running the project, ensure the following tools are installed:

- Python 3.10+
- Pip
- CMake
- C++ compiler (GCC, Clang, or MSVC)

## Installation

### 1. Clone the repository

```bash
git clone <repository-url>
cd dengue-data-engine
```


### 2. Set up Python virtual environment 
### Linux
```bash
python -m venv .venv
source .venv/bin/activate
```

### Windows
```bash
python -m venv .venv
.venv\Scripts\activate.bat
```

### 3. Install Python dependencies
```bash
pip install -r requirements.txt
```

### 4. Build the C++ core (Python extension via pybind11)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 5. Generate Dataset
```bash
python -m scripts.manage_dataset generate --start-year <start-year> --end-year <end-year>
```

## Running

```bash
uvicorn backend.main:app --reload
```

## API Documentation

After starting the server:

- Swagger UI: http://localhost:8000/docs