

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

class MergeSort : public SortingStrategy {
private:
    std::vector<int> buffer;  

    void merge(std::vector<int>& vector, std::vector<int>& idx, int min, int mid, int max) {
        int i = min;
        int j = mid + 1;
        int k = min;

        while (i <= mid && j <= max) {
            if (vector[idx[i]] <= vector[idx[j]]) {
                buffer[k] = idx[i];
                i++;
            } else {
                buffer[k] = idx[j];
                j++;
            }
            k++;
        }

        while (i <= mid) {
            buffer[k] = idx[i];
            i++;
            k++;
        }

        while (j <= max) {
            buffer[k] = idx[j];
            j++;
            k++;
        }

    
        for (int x = min; x <= max; x++) {
            idx[x] = buffer[x];
        }
    }

public:
    void sort(std::vector<int>& vector, std::vector<int>& idx, int min, int max) override {
        if (min < max) {
            if (buffer.size() < idx.size()) {
                buffer.resize(idx.size());
            }

            int mid = min + (max - min) / 2;

            sort(vector, idx, min, mid);
            sort(vector, idx, mid + 1, max);
            merge(vector, idx, min, mid, max);
        }
    }
};

class QuickSort : public SortingStrategy { 
private:
    void median_of_three(std::vector<int>& vector, std::vector<int>& idx, int min, int max) {
        int mid = min + (max - min) / 2;

        if (vector[idx[min]] > vector[idx[mid]])
            std::swap(idx[min], idx[mid]);

        if (vector[idx[min]] > vector[idx[max]])
            std::swap(idx[min], idx[max]);

        if (vector[idx[mid]] > vector[idx[max]])
            std::swap(idx[mid], idx[max]);

        // idx[mid] agora é a mediana dos três -> vira o pivô, na posição max
        std::swap(idx[mid], idx[max]);
    }

    int partition(std::vector<int>& vector, std::vector<int>&idx, int min, int max) {
        median_of_three(vector, idx, min, max);

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
        while (min < max) {
            int p = partition(vector, idx, min, max);

            // recursão só na partição menor -> limita a pilha a O(log n)
            if (p - min < max - p) {
                sort(vector, idx, min, p - 1);
                min = p + 1;
            } else {
                sort(vector, idx, p + 1, max);
                max = p - 1;
            }
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

