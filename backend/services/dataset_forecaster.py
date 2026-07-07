from statsmodels.tsa.holtwinters import ExponentialSmoothing
from backend.services.utils import date_utils
from dateutil.relativedelta import relativedelta
from abc import ABC, abstractmethod



_LATEST_DATE_RECORD = 20200417
_SEASONAL_PERIODS = 12

class ArbovirusDataForecaster(ABC):

    @abstractmethod 
    def get_dengue_forecast(self, city_code):
        pass


class DengueDataForecaster:

    def __init__(self, searcher):
        self.searcher = searcher


    def get_dengue_forecast(self, city_code):
        date_to_num_cases = self.searcher.get_num_cases_dates(_LATEST_DATE_RECORD, 20260615, city_code)
        forecast = self._generate_dengue_forecast(date_to_num_cases)
        return self._generate_forecast_dict(forecast, date_to_num_cases)


    def _generate_dengue_forecast(self, date_to_num_cases: dict):
        num_cases = [num for num in date_to_num_cases.values()]

        model = ExponentialSmoothing(
            num_cases,
            trend="add",
            seasonal="add",
            damped_trend=True,
            seasonal_periods=_SEASONAL_PERIODS,
            initialization_method="estimated"
        ).fit()

        forecast = model.forecast(12).clip(min=0)
        forecast = forecast.round(0)

        return forecast
    

    def _generate_forecast_dict(self, forecast, date_to_num_cases):
        dates = [date for date in date_to_num_cases.keys()]

        prevision_by_date = {}

        start_date = date_utils.convert_to_datetime(dates[-1])
        final_date = start_date + relativedelta(months=13)

        for i, date in enumerate(date_utils.get_intermediate_months_datetime(start_date, final_date)):
            date = date_utils.date_to_int_ym(date)
            prevision_by_date[date] = int(forecast[i])

        return prevision_by_date


