
#pragma once 

#include <vector>
#include <iostream>
#include "dengue_case.h"
#include "indexer.h"
#include <fstream>
#include <array>
#include <string>

//MUDAR NOME PARA BIN_MANAGER

class FileManager {

public:

    void truncate_bins(int year) {

        std::ofstream f;

        for (int i = 0; i < 12; i++) {
            std::string file_name =
                "backend/data/bins/file" +
                std::to_string(year) +
                (i+1 < 10 ? "0" : "") +
                std::to_string(i+1) +
                ".dat";
            f.open(file_name, std::ios::out | std::ios::binary | std::ios::trunc);
    
            if (!f) {
                std::cout << "File not exist!\n";
                continue;
            }
            
            f.close(); 
        }
    };


    void append_bin(std::vector<DengueCase> cases, int year) {
        size_t n = cases.size();
        if (n == 0) return;

        std::array<std::vector<DengueCase>, 12> cases_months;

        for (int i = 0; i < n; i++) {
            int case_year = cases[i].notification_date / 10000;


            if (case_year != year) {
                continue; 
            }

            int mes = ((cases[i].notification_date / 100) % 100) - 1;
            if (mes >= 0 && mes < 12) {
                cases_months[mes].push_back(cases[i]);
            }
        }

        std::fstream f;
        for (int i = 0; i < 12; i++) {
            if (cases_months[i].empty()) continue; 

            std::string file_name =
                "backend/data/bins/file" +
                std::to_string(year) +
                (i+1 < 10 ? "0" : "") +
                std::to_string(i+1) +
                ".dat";


            f.open(file_name, std::ios::out | std::ios::app | std::ios::binary);

            if (f) {
                f.write(reinterpret_cast<char*>(&cases_months[i][0]), sizeof(DengueCase) * cases_months[i].size());
            }
            f.close();
        }
    }

    std::vector<DengueCase> load_bin(int date) {
        std::ifstream f;
        std::string file_path = "backend/data/bins/file" + std::to_string(date) + ".dat";
        f.open(file_path, std::ios::ate | std::ios::binary);

        if (!f) {
            std::cout << "File not exist!\n";   
            return std::vector<DengueCase>();
        }

        std::streamsize size = f.tellg();

        size_t num_cases = size / sizeof(DengueCase);

        if (num_cases == 0) return {};

        std::vector<DengueCase> cases(num_cases);

        f.seekg(0, std::ios::beg);

        f.read(reinterpret_cast<char*>(&cases[0]), size);

        f.close();

        return cases;
    };


    std::vector<DengueCase> load_bin_from_index(int date, IndexRegister reg) {
        std::ifstream f;
        std::string file_path = "backend/data/bins/file" + std::to_string(date) + ".dat";

        f.open(file_path, std::ios::ate | std::ios::binary);

        if (!f) {
            std::cout << "File not exist!\n";
            return {};
        }

        std::streamsize file_size = f.tellg();
        size_t total_cases = static_cast<size_t>(file_size) / sizeof(DengueCase);

        // validação dos índices
        if (reg.start < 0 || reg.end < reg.start) {
            std::cout << "Indices invalidos!\n";
            return {};
        }

        size_t start = static_cast<size_t>(reg.start);
        size_t end   = static_cast<size_t>(reg.end);

        if (start >= total_cases) {
            std::cout << "Start fora do intervalo do arquivo!\n";
            return {};
        }

        // clamp: nao deixa ler alem do fim do arquivo
        if (end > total_cases) {
            end = total_cases;
        }

        size_t num_cases = end - start;
        if (num_cases == 0) return {};

        std::vector<DengueCase> cases(num_cases);

        std::streamoff offset = static_cast<std::streamoff>(start * sizeof(DengueCase));
        f.seekg(offset, std::ios::beg);

        f.read(reinterpret_cast<char*>(cases.data()),
            static_cast<std::streamsize>(num_cases * sizeof(DengueCase)));

        if (!f) {
            std::cout << "Erro ao ler o arquivo!\n";
            return {};
        }

        return cases;
    }

    void overwrite_bin(std::vector<DengueCase> cases, int date) {
        std::ofstream f;
        std::string file_path = "backend/data/bins/file" + std::to_string(date) + ".dat";

        f.open(file_path, std::ios::out | std::ios::binary | std::ios::trunc);

        f.write(reinterpret_cast<char*>(&cases[0]), sizeof(DengueCase) * cases.size());

        f.close();

    }

    void save_indexes(std::vector<IndexRegister> registers, int date) {
        std::ofstream f;
        std::string file_path = "backend/data/bins/index" + std::to_string(date) + ".idx";

        f.open(file_path, std::ios::out | std::ios::binary | std::ios::trunc);

        f.write(reinterpret_cast<char*>(&registers[0]), sizeof(IndexRegister) * registers.size());

        f.close();  
    }

    std::vector<IndexRegister> load_indexes(int date) {
        std::ifstream f;
        std::string file_path = "backend/data/bins/index" + std::to_string(date) + ".idx";
        f.open(file_path, std::ios::ate | std::ios::binary);

        if (!f) {
            std::cout << "File not exist!\n";   
            return std::vector<IndexRegister>();
        }

        std::streamsize size = f.tellg();

        size_t num_cases = size / sizeof(IndexRegister);

        std::vector<IndexRegister> registers(num_cases);

        f.seekg(0, std::ios::beg);

        f.read(reinterpret_cast<char*>(&registers[0]), size);

        f.close();

        return registers;
    }

};