#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "undirected_graph.hpp"
#include "array_list.hpp"
#include "util.hpp"


class menu {
private:
    ds::undirected_graph g;
    int choice; 
    int algorithm_choice;
    bool cost_matrix_set = false;
    bool tsp_algorithm_set = false;

public:
    void start_menu();

    void print_main_menu();
    void print_graph_menu();
    void print_tsp_menu();

    void get_choice();
    void get_graph_input();
    void get_tsp_algorithm();
    
    void solve_tsp();
};

void menu::get_tsp_algorithm() {
    do {
        std::cout << "Choose an algorithm: ";
        std::cin >> algorithm_choice;
        clear_input();

        if (algorithm_choice < 1 || algorithm_choice > 3) {
            std::cout << "Invalid choice";
        }
    } while (algorithm_choice < 1 || algorithm_choice > 3);

    if (algorithm_choice != 3) {
        tsp_algorithm_set = true;
    }
}

void menu::get_choice() {
    do {
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clear_input();

        if (choice < 1 || choice > 4) {
            std::cout << "Invalid choice" << std::endl;
        }
    } while (choice < 1 || choice > 4);
}

void menu::get_graph_input() {
    int input_choice;

    do {
        std::cout << "Enter input method: ";
        std::cin >> input_choice;
        clear_input();

        if (input_choice < 1 || input_choice > 3) {
            std::cout << "Invalid choice" << std::endl;
        }

    } while (input_choice < 1 || input_choice > 3);

    if (input_choice == 1) {
        std::string file_name;
        std::cout << "Enter file name: ";
        std::cin >> file_name;
        clear_input();

        auto a = util::read_matrix_from_file(file_name);
        util::print_matrix(a);

        g.set_cost_matrix(a);
    } else if (input_choice == 2) {
        int size;
        int lb;
        int hb;

        std::cout << "Enter graph size: ";
        std::cin >> size;
        clear_input();
        std::cout << "Enter cost lower bound: ";
        std::cin >> lb;
        clear_input();
        std::cout << "Enter cost higher bound: ";
        std::cin >> hb;
        clear_input();

        g.set_cost_matrix(util::generate_symmetric_cost_matrix(size, lb, hb));

        std::cout << "Generated random graph" << std::endl;
        std::cout << g << std::endl;
    } else if (input_choice == 3) {
        return;
    }

    cost_matrix_set = true;
}

void menu::solve_tsp() {
    if (!tsp_algorithm_set || !cost_matrix_set) {
        std::cout << "Cost matrix or algorithm has not been set" << std::endl;
        return;
    }

    if (algorithm_choice == 1) {
        auto [min_cost, tour] = g.tsp_brute_force(0);

        std::cout << "Min cost: " << min_cost << std::endl;
        std::cout << "Min tour: ";
        util::print_array(tour); std::cout << std::endl;
    } else if (algorithm_choice == 2) {
        auto [min_cost, tour] = g.tsp_bnb_v2(0);

        std::cout << "Min cost: " << min_cost << std::endl;
        std::cout << "Min tour: ";
        util::print_array(tour); std::cout << std::endl;
    }
}

void menu::start_menu() {
    for (;;) {
        print_main_menu();
        get_choice();

        if (choice == 1) {
            print_graph_menu();
            get_graph_input();
        } else if (choice == 2) {
            print_tsp_menu();
            get_tsp_algorithm();
        } else if (choice == 3) {
            solve_tsp();
        } else if (choice == 4) {
            break;
        }
    }
}


void menu::print_main_menu() {
    std::cout << std::endl;
    std::cout << "   Traveling Salesman Solver" << std::endl;
    std::cout << "1. Input cost matrix" << std::endl;
    std::cout << "2. Input TSP algorithm" << std::endl;
    std::cout << "3. Solve TSP" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void menu::print_graph_menu() {
    std::cout << std::endl;
    std::cout << "   Graph Input Method" << std::endl;
    std::cout << "1. File" << std::endl;
    std::cout << "2. Random" << std::endl;
    std::cout << "3. Return" << std::endl;
}

void menu::print_tsp_menu() {
    std::cout << std::endl;
    std::cout << "   TSP algorithm" << std::endl;
    std::cout << "1. Brute force" << std::endl;
    std::cout << "2. Branch and bound" << std::endl;
    std::cout << "3. Return" << std::endl;
}


#endif