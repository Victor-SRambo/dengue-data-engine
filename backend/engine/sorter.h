

#pragma once

#include <vector>
#include "dengue_case.h"


class QuickSort { 

public:
    void quicksort(std::vector<int>& vector, std::vector<int>&idx, int min, int max) {
        if (min < max) {
            int p = partition(vector, idx, min, max);
            quicksort(vector, idx, min, p-1);
            quicksort(vector, idx, p+1, max);
        }
    }

    int partition(std::vector<int>& vector, std::vector<int>&idx, int min, int max) {
        int i = min - 1;

        for (int j = min; j < max; j++) {
            if (vector[idx[j]] < vector[idx[max]]) {
                i++;
                std::swap(idx[i], idx[j]);
            }
        }

        std::swap(idx[i+1], idx[max]);
        return i+1;
    }
};


class CaseSorter {
public:
    std::vector<int> sort(std::vector<DengueCase> cases) {

        std::vector<int> vector;
        std::vector<int> indexes;
        size_t size = cases.size();

        for (int i = 0; i < size; i++) {
            vector.push_back(cases[i].city_notification_code);
            indexes.push_back(i);
        }


        QuickSort sorting;

        sorting.quicksort(vector, indexes, 0, size-1);

        return indexes;
    };
};


