#include "fluid_system.hpp"

std::vector<std::shared_ptr<fluid_cell>> cells;
void fluid_system::update() {
    std::vector<fluid_cell> cells_original;
    for (std::shared_ptr<fluid_cell> c : cells) c->set_pre_update_state();
    for (std::shared_ptr<fluid_cell> c : cells) c->update(delta_t);
}
void fluid_system::add_cell(fluid_cell c, std::vector<std::shared_ptr<fluid_cell>> attach_low, std::vector<std::shared_ptr<fluid_cell>> attach_high) {
    c.neighbors_low = attach_low;
    c.neighbors_high = attach_high;
    cells.push_back(std::make_shared<fluid_cell>(c));
}
void fluid_system::add_cell(fluid_cell c) {
    if (cells.size() == 0) add_cell(c, {}, {});
    add_cell(c, {cells.back()}, {});
}
bool fluid_system::valid_index(size_t index) {
    if (index < 0) return false;
    if (index >= cells.size()) return false;
    return true;
}