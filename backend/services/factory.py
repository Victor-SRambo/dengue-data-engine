

from backend.integration import dados_abertos
from backend.services import csv_list_converter, csv_loader, csv_normalizer
from backend.services import dataset_builder, dataset_importer, dataset_searcher, dataset_storer, dataset_forecaster
from build.Debug import dengue, case_sorter


def create_dengue_dataset_importer():
    http_client = dados_abertos.DengueHttpClient()
    return dataset_importer.DengueDataImporter(client=http_client)


def create_dengue_dataset_storer():
    normalizer = csv_normalizer.DengueNormalizer()

    loader = csv_loader.DengueLoader(normalizer=normalizer)
    list_converter = csv_list_converter.DengueListConverter()
    mapper = dengue.DadosAbertosMapper()
    file_manager = dengue.FileManager()

    return dataset_storer.DengueDataStorer(loader=loader,
                                           list_converter=list_converter,
                                           mapper=mapper,
                                           file_manager=file_manager)


def create_dengue_dataset_builder():
    file_manager = dengue.FileManager()
    sorting_method = case_sorter.MergeSort()
    sorter = case_sorter.CaseSorter(sorting_method)
    indexer = dengue.Indexer()

    return dataset_builder.DengueDataBuilder(file_manager=file_manager,
                                             sorter=sorter,
                                             indexer=indexer)


def create_dengue_dataset_searcher():
    file_manager = dengue.FileManager()
    binary_searcher=dengue.BinarySearch()

    return dataset_searcher.DengueDataSearcher(file_manager=file_manager, 
                                               binary_searcher=binary_searcher)


def create_dengue_dataset_forecaster():
    searcher = create_dengue_dataset_searcher()

    return dataset_forecaster.DengueDataForecaster(searcher=searcher)

