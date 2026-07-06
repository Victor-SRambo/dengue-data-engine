from dateutil.relativedelta import relativedelta
from datetime import datetime

_months_per_year = 12

def convert_to_datetime(date):
    date = str(date)

    if len(date) == 4:
        date = date + "01"

    if len(date) == 6:
        date = date + "01"


    return datetime.strptime(date, "%Y%m%d")


def date_to_int_ymd(date):
    return int(date.strftime("%Y%m%d"))


def date_to_int_ym(date):
    return int(date.strftime("%Y%m"))


def date_to_int_y_full(date):
    return int(date.strftime("%Y"))

def date_to_int_y_short(date):
    return int(date.strftime("%y"))



def get_intermediate_months_datetime(start_date, end_date):
    current_date = start_date + relativedelta(months=1)

    while current_date < end_date:
        yield current_date
        current_date += relativedelta(months=1)


def get_all_months_datetime(start_date, end_date):
    current_date = start_date

    while current_date <= end_date:
        yield current_date
        current_date += relativedelta(months=1)

def get_all_years_datetime(start_date, end_date):
    current_date = start_date

    while current_date <= end_date:
        yield current_date
        current_date += relativedelta(years=1)