#pragma once
#include <vector>
#include <memory>
#include "cell.hpp"

namespace fluid {

struct system {
    double delta_t;
    std::vector<std::shared_ptr<cell>> cells;
    system(double delta_t_);
    void update();
    void add_cell(cell c, std::vector<std::shared_ptr<cell>> attach_low, std::vector<std::shared_ptr<cell>> attach_high);
    void add_cell(cell c);
    bool valid_index(size_t index);
    std::string str();
};

}