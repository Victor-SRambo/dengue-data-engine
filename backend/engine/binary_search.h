#pragma once 

#include <vector>
#include <array>
#include <optional>
#include "dengue_case.h"
#include "case_indexer.h"

template <typename Arbovirus>
class BinarySearch {
public:
    std::optional<IndexRegister> index_search(const std::vector<IndexRegister>& registers, int target_code) {

        int m;
        int l = 0;
        int r = registers.size()-1;

        while (l<=r) {
            m = (l+r)/2;

            if (registers[m].city_notification_code > target_code) {
                r = m-1;
            }
            else if (registers[m].city_notification_code < target_code) {
                l = m+1;
            }
            else {
                return registers[m];
            }
        }

        return std::nullopt;
    }


    int after_date_search(
        const std::vector<Arbovirus>& cases,
        int date)
    {
        int l = 0;
        int r = cases.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;

            if (cases[m].notification_date < date) {
                l = m + 1;
            }
            else if (cases[m].notification_date > date) {
                r = m - 1;
            }
            else {
                while(m>0 && cases[m-1].notification_date == date) {
                    m--;
                }

                return m;
            }

        }

        return l;
    }


    int before_date_search(
        const std::vector<Arbovirus>& cases,
        int date)
    {

        int l = 0;
        int r = cases.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;

            if (cases[m].notification_date < date) {
                l = m + 1;                
            }
            else if (cases[m].notification_date > date) {
                r = m - 1;                
            }
            else {
                while(m + 1 < cases.size() && cases[m+1].notification_date == date) {
                    m++;
                }

                return m;
            }

        }
        return r;
    }
};