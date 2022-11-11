#include "util.hpp"
#include "array_list.hpp"


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <random>

namespace util {
    void read_matrix_from_file(std::string file_path, ds::array_list<ds::array_list<int>> &matrix) {
        std::ifstream file(file_path);
        ds::array_list<int> current_row;
        int num;


        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ssin(line);
                while (ssin >> num) {
                    current_row.push_back(num);
                };
                matrix.push_back(current_row);
                current_row.clear();
            }
        } else {
            std::cout << "Can't open file" << std::endl;
        }
    }

    void print_matrix(ds::array_list<ds::array_list<int>> &matrix) {
        for (auto &row : matrix) {
            for (auto &cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    void print_array(ds::array_list<int> &a) {
        for (int i = 0; i < a.size(); ++i) {
            std::cout << a[i] << " ";
        }
    }

    ds::array_list<ds::array_list<int>> generate_cost_matrix(int size, int cost_low_bound, int cost_high_bound) {
        ds::array_list<ds::array_list<int>> ret(size, ds::array_list<int>(size, 0));

        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                ret[i][j] = generate_random_num(cost_low_bound, cost_high_bound);
                ret[j][i] = ret[i][j];
            }
        }

        return ret;
    }

    int generate_random_num(const int &start, const int &end) {
        std::random_device dev;
        std::mt19937 rgn(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distribute(start, end);

        return distribute(rgn);
    }
}