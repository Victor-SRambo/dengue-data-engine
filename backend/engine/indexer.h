
#pragma once

#include <vector>
#include <array>
#include "dengue_case.h"




struct IndexRegister {
    int city_notification_code;
    long int start;
    long int end;
};


class Indexer {

public:

    std::vector<IndexRegister> create_index(std::vector<DengueCase> cases) {
        
        std::vector<IndexRegister> indexes;


        size_t size = cases.size();
        int last_city_code = 0;
        int register_i = -1;

        for (size_t i = 0; i < size; i++) {
            if(cases[i].city_notification_code != last_city_code) {
                IndexRegister registers;
                registers.city_notification_code = cases[i].city_notification_code;
                registers.start = i;
                registers.end = i;

                last_city_code = registers.city_notification_code;
                indexes.push_back(registers);

                register_i++;
            }

            indexes[register_i].end++;
        }

        return indexes;
    }
};