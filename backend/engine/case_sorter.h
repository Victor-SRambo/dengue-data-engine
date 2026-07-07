

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "sorting.h"
#include "dengue_case.h"




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
    virtual int extract(const DengueCase& c) = 0;
};


class DateField : public CaseSortingField {
protected:
    int extract(const DengueCase& c) override {
        return c.notification_date;
    }
};


class CityCodeField : public CaseSortingField {
protected:
    int extract(const DengueCase& c) override {
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

