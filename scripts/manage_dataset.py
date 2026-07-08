import argparse
from backend.services import factory


def handle_import(args):
    dataset_importer = factory.create_dengue_dataset_importer()
    dataset_importer.import_years(args.start_year, args.end_year)


def handle_store(args):
    dataset_storer = factory.create_dengue_dataset_storer()
    dataset_storer.store_years(args.start_year, args.end_year)


def handle_build(args):
    dataset_builder = factory.create_dengue_dataset_builder()
    dataset_builder.build_years(args.start_year, args.end_year)


def handle_generate_dataset(args):
    handle_import(args)
    handle_store(args)
    handle_build(args)


def main():
    parser = argparse.ArgumentParser(description="Dataset Manager")
    
    # Criamos um parser compartilhado para não duplicar os argumentos de ano
    parent_parser = argparse.ArgumentParser(add_help=False)
    parent_parser.add_argument(
        "--start-year", 
        type=int, 
        required=True, 
        help="Ano inicial do processamento (Ex: 2020)"
    )
    parent_parser.add_argument(
        "--end-year", 
        type=int, 
        required=True, 
        help="Ano final do processamento (Ex: 2026)"
    )

    subparser = parser.add_subparsers(dest="command", required=True)

    # Map command: import
    parser_import = subparser.add_parser("import", help="Import raw dataset years", parents=[parent_parser])
    parser_import.set_defaults(func=handle_import)

    # Map command: store
    parser_store = subparser.add_parser("store", help="Store processed dataset years", parents=[parent_parser])
    parser_store.set_defaults(func=handle_store)

    # Map command: build
    parser_build = subparser.add_parser("build", help="Build binary indexes from data", parents=[parent_parser])
    parser_build.set_defaults(func=handle_build)

    # Map command: generate
    parser_generate = subparser.add_parser("generate", help="Generate final dataset months", parents=[parent_parser])
    parser_generate.set_defaults(func=handle_generate_dataset)

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()