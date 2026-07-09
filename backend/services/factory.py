

from backend.integration import dados_abertos
from backend.services import csv_list_converter, csv_loader, csv_normalizer
from backend.services import dataset_builder, dataset_importer, dataset_searcher, dataset_storer, dataset_forecaster
from backend.services import data_logger
from build.modules import dengue, engine

def create_dengue_dataset_importer() -> dataset_importer.DengueDataImporter:
    http_client = dados_abertos.DengueHttpClient()
    logger = data_logger.ImporterLogger()
    return dataset_importer.DengueDataImporter(client=http_client,
                                               logger=logger)


def create_dengue_dataset_storer() -> dataset_storer.DengueDataStorer:
    normalizer = csv_normalizer.DengueNormalizer()
    loader = csv_loader.DengueLoader()
    list_converter = csv_list_converter.DengueListConverter()
    mapper = dengue.DengueCaseMapper()
    file_manager = engine.DengueBinaryFileManager()
    logger = data_logger.StorerLogger()

    return dataset_storer.DengueDataStorer(loader=loader,
                                           normalizer=normalizer,
                                           list_converter=list_converter,
                                           mapper=mapper,
                                           file_manager=file_manager,
                                           logger=logger)


def create_dengue_dataset_builder() -> dataset_builder.DengueDataBuilder:
    file_manager = engine.DengueBinaryFileManager()
    sorting_method = engine.MergeSort()
    sorter = engine.DengueCaseSorter(sorting_method)
    indexer = engine.DengueCaseIndexer()
    logger = data_logger.BuilderLogger()


    return dataset_builder.DengueDataBuilder(file_manager=file_manager,
                                             sorter=sorter,
                                             indexer=indexer,
                                             logger=logger)


def create_dengue_dataset_searcher() -> dataset_searcher.DengueDataSearcher:
    file_manager = engine.DengueBinaryFileManager()
    binary_searcher= engine.DengueBinarySearch()

    return dataset_searcher.DengueDataSearcher(file_manager=file_manager, 
                                               binary_searcher=binary_searcher)


def create_dengue_dataset_forecaster() -> dataset_forecaster.DengueDataForecaster:
    searcher = create_dengue_dataset_searcher()

    return dataset_forecaster.DengueDataForecaster(searcher=searcher)

