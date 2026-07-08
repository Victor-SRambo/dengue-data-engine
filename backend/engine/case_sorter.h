

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "sorting.h"
#include "dengue_case.h"


template <typename Arbovirus>
class CaseSortingField {
public:
    void get_field(std::vector<int>& field_cases, std::vector<Arbovirus>& cases, std::vector<int>& indexes) {
        size_t size = cases.size();

        for (size_t i = 0; i < size; i++) {
            field_cases.push_back(extract(cases[i]));
            indexes.push_back(i);
        }        
    }

    virtual ~CaseSortingField() = default;

protected:
    virtual int extract(const Arbovirus& c) = 0;
};


template <typename Arbovirus>
class DateField : public CaseSortingField<Arbovirus> {
protected:
    int extract(const Arbovirus& c) override {
        return c.notification_date;
    }
};


template <typename Arbovirus>
class CityCodeField : public CaseSortingField<Arbovirus> {
protected:
    int extract(const Arbovirus& c) override {
        return c.city_notification_code;
    }
};


template <typename Arbovirus>
class CaseSorter {
private:
    std::shared_ptr<SortingStrategy> _sorting;

public:

    CaseSorter(std::shared_ptr<SortingStrategy> sorting) 
        : _sorting(sorting) {}


    std::vector<int> sort(std::vector<Arbovirus>& cases, std::shared_ptr<CaseSortingField<Arbovirus>> field) {
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

