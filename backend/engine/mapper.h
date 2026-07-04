
#pragma once 

#include <vector>
#include "dengue_case.h"

class CaseMapper {

};


struct DengueFieldVectors{

    std::vector<int> notification_dates;
    std::vector<int> first_symptoms_dates;
    std::vector<int> epidemiological_weeks;

    std::vector<int> state_notification_codes;
    std::vector<int> city_notification_codes;

    std::vector<int> state_living_codes;
    std::vector<int> city_living_codes;

    std::vector<int> ages;
    std::vector<int> year_births;
    std::vector<int> escolarities;
    std::vector<int> professions;
    std::vector<int> pregnancy_states;
    std::vector<int> ethnicities;

    std::vector<char> sexes;
};


class DadosAbertosMapper {

public:
    std::vector<DengueCase> mapDengueCase(DengueFieldVectors v) {

        size_t size = v.notification_dates.size();
        std::vector<DengueCase> cases;

        for (int i = 0; i < size; i++) {
            DengueCase c;
            c.notification_date = v.notification_dates[i];
            c.first_symptoms_date = v.first_symptoms_dates[i];
            c.epidemiological_week = v.epidemiological_weeks[i];
            c.state_notification_code = v.state_notification_codes[i];
            c.city_notification_code = v.city_notification_codes[i];
            c.state_living_code = v.state_living_codes[i];
            c.city_living_code = v.city_living_codes[i];
            c.age = v.ages[i];
            c.year_birth = v.year_births[i];
            c.escolarity = v.escolarities[i];
            c.profession = v.professions[i];
            c.pregnacy_state = v.pregnancy_states[i];
            c.ethnicity = v.ethnicities[i];
            c.sex = v.sexes[i];
            
            cases.push_back(c);
        }

        return cases;

    }

    
};