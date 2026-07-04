
#pragma once 

#include <vector>
#include <iostream>
#include "dengue_case.h"
#include <fstream>
#include <array>
#include <string>

//MUDAR NOME PARA BIN_MANAGER

class FileManager {

public:

    void truncate_bins(int year) {

        std::ofstream f;

        for (int i = 1; i <= 12; i++) {
            std::string file_name = "backend/data/bins/file" + std::to_string(year) + std::to_string(i) + ".dat";
            f.open(file_name, std::ios::out | std::ios::binary | std::ios::trunc);
    
            if (!f) {
                std::cout << "File not exist!\n";
                continue;
            }
            
            f.close(); 
        }
    };


    void append_bin(std::vector<DengueCase> cases) {

        size_t n = cases.size();

        std::array<std::vector<DengueCase>, 12> cases_months;

        int year = cases[0].notification_date / 10000;

        for (int i = 0; i < n; i++) {
            int mes = ((cases[i].notification_date / 100) % 100) - 1;


            if (mes >= 0 && mes < 12) {
                cases_months[mes].push_back(cases[i]);
            }
        }

        std::fstream f;

        for (int i = 0; i < 12; i++) {

            if (cases_months[i].empty()) {
                continue; 
            }

            std::string file_name = "backend/data/bins/file" + std::to_string(year) + std::to_string(i+1) + ".dat";


            f.open(file_name, std::ios::app | std::ios::binary);

            if (f) {
                f.write(reinterpret_cast<char*>(&cases_months[i][0]), sizeof(DengueCase) * cases_months[i].size());
            }
            else {
                std::cout << "error opening csv \n";
            }

            f.close();
        }

    };


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

        std::vector<DengueCase> cases(num_cases);

        f.seekg(0, std::ios::beg);

        f.read(reinterpret_cast<char*>(&cases[0]), size);

        f.close();

        return cases;
    
    };

};