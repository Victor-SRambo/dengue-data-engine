

from build.Debug import dengue
from backend.services import dataset_importer, dataset_storer, dataset_builder
from backend.integration import dados_abertos
from fastapi import FastAPI

app = FastAPI()

@app.get("/pedroammes")
def root(nome: str):
    return {"Hello": f"{nome}"}

"""
loader = csv_loader.DengueLoader(
    csv_normalizer.DengueNormalizer()
)

importer = importer.DengueImporter()
normalizer = csv_normalizer.DengueNormalizer()
mapper = dengue.DadosAbertosMapper()
file_manager = dengue.FileManager()
file_manager.truncate_bins(2026)
list_converter = csv_list_converter.DengueListConverter()


for df_batch in loader.batch_load_csv(26):

    df_batch = normalizer.normalize_cases_csv(df_batch)

    fields = list_converter.to_list(df_batch)

    dengue_cases = mapper.mapDengueCase(fields)

    file_manager.append_bin(dengue_cases)

file_manager = dengue.FileManager()
sorter = dengue.CaseSorter()
sorter.select_field(dengue.CaseCityCodeField())
indexer = dengue.Indexer();

data = file_manager.load_bin(20263)

sorted_indexes = sorter.sort(data)
sorted_data = [data[i] for i in sorted_indexes]

indexes = indexer.create_index(sorted_data);

sorter.select_field(dengue.CaseDateField())

final_sorted = []

for index in indexes:
    chunk = sorted_data[index.start:index.end]

    idx = sorter.sort(chunk)
    sorted_chunk = [chunk[i] for i in idx]

    final_sorted.extend(sorted_chunk)

for case in final_sorted:
    print(f"{case.city_notification_code} - {case.notification_date}")

print("All Done!!!")

"""



#dataset_importer = dataset_importer.DengueDataImporter(dados_abertos.DengueHttpClient())
#dataset_importer.import_years(2025,2026)

#dataset_storer = dataset_storer.DengueDataStorer()
#dataset_storer.store_years(2025,2026)

dataset_builder = dataset_builder.DengueDataBuilder()
dataset_builder.build_years(2025,2025)