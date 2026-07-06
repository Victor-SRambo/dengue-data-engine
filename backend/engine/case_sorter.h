

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "dengue_case.h"


class SortingStrategy {
public:
    virtual void sort(std::vector<int>& vector, std::vector<int>&idx, int min, int max) = 0;
    virtual ~SortingStrategy() = default;

};


class QuickSort : public SortingStrategy { 
private:
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

public:
    void sort(std::vector<int>& vector, std::vector<int>&idx, int min, int max) override {
        if (min < max) {
            int p = partition(vector, idx, min, max);
            sort(vector, idx, min, p-1);
            sort(vector, idx, p+1, max);
        }
    }
};


class CaseSortingField {
public:
    void get_field(std::vector<int>& field_cases, std::vector<DengueCase>& cases, std::vector<int>& indexes) {
        size_t size = cases.size();

        for (size_t i = 0; i < size; i++) {
            field_cases.push_back(extract(cases[i]));
            indexes.push_back(i);
        }        
    }

    virtual ~CaseSortingField() = default;

protected:
    virtual int extract(DengueCase& c) = 0;
};


class DateField : public CaseSortingField {
protected:
    int extract(DengueCase& c) override {
        return c.notification_date;
    }
};


class CityCodeField : public CaseSortingField {
protected:
    int extract(DengueCase& c) override {
        return c.city_notification_code;
    }
};



class CaseSorter {
private:
    std::shared_ptr<SortingStrategy> _sorting;

public:

    CaseSorter(std::shared_ptr<SortingStrategy> sorting) 
        : _sorting(sorting) {}


    std::vector<int> sort(std::vector<DengueCase>& cases, std::shared_ptr<CaseSortingField> field) {
        size_t size = cases.size();

        std::vector<int> field_cases;
        std::vector<int> indexes;

        field_cases.reserve(size);
        indexes.reserve(size);
        
        if(!field) {
            throw std::runtime_error("Field was not selected for sorting");
        }

        if (size == 0) {
            return indexes; 
        }
        field->get_field(field_cases, cases, indexes);
        _sorting->sort(field_cases, indexes, 0, size-1);
        
        return indexes;
    }
};

