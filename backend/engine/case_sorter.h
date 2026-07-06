

#pragma once

#include <vector>
#include "dengue_case.h"


class SortingStrategy {
public:
    virtual void sort(std::vector<int>& vector, std::vector<int>&idx, int min, int max) = 0;
    virtual int partition(std::vector<int>& vector, std::vector<int>&idx, int min, int max) = 0;
    virtual ~SortingStrategy() = default;

};


class QuickSort : public SortingStrategy { 
public:
    void sort(std::vector<int>& vector, std::vector<int>&idx, int min, int max) override {
        if (min < max) {
            int p = partition(vector, idx, min, max);
            sort(vector, idx, min, p-1);
            sort(vector, idx, p+1, max);
        }
    }

    int partition(std::vector<int>& vector, std::vector<int>&idx, int min, int max) override {
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


class CaseSortingField {
public:
    virtual void field(std::vector<DengueCase>& cases, std::vector<int>& vector, std::vector<int>& indexes) = 0;
    virtual ~CaseSortingField() = default;
};


class DateField : public CaseSortingField {
public:
    void field(std::vector<DengueCase>& cases, std::vector<int>& vector, std::vector<int>& indexes) override {
        size_t size = cases.size();

        for (int i = 0; i < size; i++) {
            vector.push_back(cases[i].notification_date);
            indexes.push_back(i);
        }
    }
};


class CityCodeField : public CaseSortingField {
public:
    void field(std::vector<DengueCase>& cases, std::vector<int>& vector, std::vector<int>& indexes) override {
        size_t size = cases.size();

        for (int i = 0; i < size; i++) {
            vector.push_back(cases[i].city_notification_code);
            indexes.push_back(i);
        }
    }
};





class CaseSorter {
private:
    std::shared_ptr<SortingStrategy> _sorting;

public:

    CaseSorter(std::shared_ptr<SortingStrategy> sorting) 
        :   _sorting(sorting) {}


    std::vector<int> sort(std::vector<DengueCase> cases, std::shared_ptr<CaseSortingField> field) {

        std::vector<int> vector;
        std::vector<int> indexes;
        
        size_t size = cases.size();

        if(!field) {
            throw std::runtime_error("Field was not selected for sorting");
        }

        field->field(cases, vector, indexes);
        _sorting->sort(vector, indexes, 0, size-1);

        return indexes;
    }
};

