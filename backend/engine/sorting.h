#pragma once

#include <vector>
#include <algorithm>

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
