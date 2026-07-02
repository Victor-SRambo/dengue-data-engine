
#pragma once 

#include <vector>
#include "dengue_case.h"

class CaseMapper {

};

//wraper seria melhor nome
class DadosAbertosMapper {

public:
    std::vector<DengueCase> mapDengueCase(
        std::vector<int> ages,
        std::vector<int> notification_dates,
        std::vector<int> first_symptoms_dates) {

        size_t n = notification_dates.size();
        std::vector<DengueCase> cases;

        for (int i = 0; i < n; i++) {
            DengueCase c;
            c.notification_date = notification_dates[i];
            c.first_symptoms_date = first_symptoms_dates[i];
            c.age = ages[i];

            cases.push_back(c);
        }

        return cases;

    }

    
};