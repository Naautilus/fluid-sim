#pragma once
#include <vector>
#include <memory>
#include "fluid_cell.hpp"

struct fluid_system {
    double delta_t;
    std::vector<std::shared_ptr<fluid_cell>> cells;
    void update();
    void add_cell(fluid_cell c, std::vector<std::shared_ptr<fluid_cell>> attach_low, std::vector<std::shared_ptr<fluid_cell>> attach_high);
    void add_cell(fluid_cell c);
    bool valid_index(size_t index);
};
