#pragma once 

#include <vector>
#include <iostream>
#include "dengue_case.h"
#include "case_indexer.h"
#include <fstream>
#include <array>
#include <string>
#include <optional>


template <typename Arbovirus>
class BinaryFileManager {
private:
    std::string _cases_folder_path;
    std::string _cases_file_termination;
    std::string _cases_file_prefix;

    std::string _index_folder_path;
    std::string _index_file_termination;
    std::string _index_file_prefix;

    static constexpr int NUM_MONTHS = 12;

public:

    BinaryFileManager(std::string cases_folder_path = "backend/data/bins/",
                std::string cases_file_termination = ".dat",
                std::string cases_file_prefix = "file",
                std::string index_folder_path = "backend/data/bins/",
                std::string index_file_termination = ".idx",
                std::string index_file_prefix = "index")

        : _cases_folder_path(cases_folder_path),
          _cases_file_termination(cases_file_termination),
          _cases_file_prefix(cases_file_prefix),
          _index_folder_path(index_folder_path),
          _index_file_termination(index_file_termination),
          _index_file_prefix(index_file_prefix) {}

          
    void truncate_cases_year_bin(int date_y_full) {

        std::ofstream f;

        for (int i = 0; i < NUM_MONTHS; i++) {
            std::string month = (i+1 < 10 ? "0" : "") + std::to_string(i+1);
            std::string date_ym = std::to_string(date_y_full) + month;
            std::string file_name = _cases_file_prefix + date_ym;
            std::string file_path = _cases_folder_path + file_name + _cases_file_termination;

            f.open(file_path, std::ios::out | std::ios::binary | std::ios::trunc);
    
            if (!f) {
                std::cout << "File not found\n";
                continue;
            }
            
            f.close(); 
        }
    };


    void append_cases_year_bin(const std::vector<Arbovirus>& cases, int date_y_full) {
        if (cases.empty()) {
            return;
        } 

        size_t num_cases = cases.size();

        std::array<std::vector<Arbovirus>, NUM_MONTHS> cases_month_buffer;

        for (size_t i = 0; i < num_cases; i++) {
            int case_date_y_full = cases[i].notification_date / 10000; //take yyyy of date format yyyymmdd

            if (case_date_y_full != date_y_full) {
                continue; 
            }

            int month = ((cases[i].notification_date / 100) % 100); //take mm of date format yyyymmdd

            if (month > 0 && month <= NUM_MONTHS) {
                cases_month_buffer[month-1].push_back(cases[i]);
            }
        }

        std::ofstream f;

        for (int i = 0; i < NUM_MONTHS; i++) {
            if (cases_month_buffer[i].empty()) {
                continue;
            }

            std::string month = (i+1 < 10 ? "0" : "") + std::to_string(i+1);
            std::string date_ym = std::to_string(date_y_full) + month;
            std::string file_name = _cases_file_prefix + date_ym;
            std::string file_path = _cases_folder_path + file_name + _cases_file_termination;

            f.open(file_path, std::ios::out | std::ios::app | std::ios::binary);

            if (f) {
                f.write(reinterpret_cast<const char*>(cases_month_buffer[i].data()), sizeof(Arbovirus) * cases_month_buffer[i].size());
            }
            f.close();
        }
    }

    std::optional<std::vector<Arbovirus>> load_cases_date_bin(int date_ym) {
        std::ifstream f;
        std::string file_name = _cases_file_prefix + std::to_string(date_ym) + _cases_file_termination;
        std::string file_path = _cases_folder_path + file_name;

        f.open(file_path, std::ios::ate | std::ios::binary);


        if (!f) {
            std::cout << "Error opening file \n";
            return std::nullopt;
        }

        std::streamsize size = f.tellg();

        size_t num_cases =  static_cast<size_t>(size) / sizeof(Arbovirus);

        if (num_cases == 0) {
            return std::nullopt;
        } 

        std::vector<Arbovirus> cases(num_cases);

        f.seekg(0, std::ios::beg);

        f.read(reinterpret_cast<char*>(cases.data()), size);

        f.close();

        return cases;
    };

    void overwrite_cases_bin(const std::vector<Arbovirus>& cases, int date) {
        std::ofstream f;
        std::string file_name = _cases_file_prefix + std::to_string(date) + _cases_file_termination;
        std::string file_path = _cases_folder_path + file_name;

        f.open(file_path, std::ios::out | std::ios::binary | std::ios::trunc);

        f.write(reinterpret_cast<const char*>(&cases[0]), sizeof(Arbovirus) * cases.size());

        f.close();
    }


    std::optional<std::vector<Arbovirus>> load_cases_from_index_bin(int date, const IndexRegister reg) {
        std::ifstream f;
        std::string file_name = _cases_file_prefix + std::to_string(date) + _cases_file_termination;
        std::string file_path = _cases_folder_path + file_name;

        f.open(file_path, std::ios::ate | std::ios::binary);


        if (!f) {
            std::cout << file_path << " Path doesn't exist, failed to load cases from index\n";
            return std::nullopt;
        }

        std::streamsize file_size = f.tellg();
        size_t total_cases = static_cast<size_t>(file_size) / sizeof(Arbovirus);

        if (reg.start < 0 || reg.end < reg.start) {
            std::cout << "Indices invalidos!\n";
            return std::nullopt;
        }

        size_t start = static_cast<size_t>(reg.start);
        size_t end = static_cast<size_t>(reg.end);


        if (start >= total_cases) {
            std::cout << "Start fora do intervalo do arquivo!\n";
            return std::nullopt;
        }

        if (end > total_cases) {
            end = total_cases;
        }

        size_t num_cases = end - start;

        if (num_cases == 0) {
            return std::nullopt;
        }

        std::vector<Arbovirus> cases(num_cases);

        std::streamoff offset = static_cast<std::streamoff>(start * sizeof(Arbovirus));
        f.seekg(offset, std::ios::beg);

        f.read(reinterpret_cast<char*>(cases.data()),
            static_cast<std::streamsize>(num_cases * sizeof(Arbovirus)));

        if (!f) {
            std::cout << "Erro ao ler o arquivo!\n";
            return std::nullopt;
        }

        return cases;
    }


    void overwrite_city_indexes(const std::vector<IndexRegister>& registers, int date) {
        std::ofstream f;
        std::string file_name = _index_file_prefix + std::to_string(date) + _index_file_termination;
        std::string file_path = _index_folder_path + file_name;


        f.open(file_path, std::ios::out | std::ios::binary | std::ios::trunc);

        f.write(reinterpret_cast<const char*>(&registers[0]), sizeof(IndexRegister) * registers.size());

        f.close();  
    }

    std::optional<std::vector<IndexRegister>> load_city_indexes(int date) {
        std::ifstream f;
        std::string file_name = _index_file_prefix + std::to_string(date) + _index_file_termination;
        std::string file_path = _index_folder_path + file_name;

        f.open(file_path, std::ios::ate | std::ios::binary);

        if (!f) {
            std::cout << file_path << " Path doesn't exist, failed to load city indexes\n";   
            return std::nullopt;
        }

        std::streamsize size = f.tellg();

        size_t num_cases = static_cast<size_t>(size / sizeof(IndexRegister));

        std::vector<IndexRegister> registers(num_cases);

        f.seekg(0, std::ios::beg);

        f.read(reinterpret_cast<char*>(&registers[0]), size);

        f.close();

        return registers;
    }

};