#include "fluid_cell.hpp"
#include "fluid_system.hpp"

fluid_cell::fluid_cell(dimensions dimensions__, state state__) {
    dimensions_ = dimensions__;
    state_ = state__;
}
void fluid_cell::set_pre_update_state() {
    pre_update_state = state_;
}
void fluid_cell::update(double delta_t) {
    std::cout << "cell " << this << " updating: " << pre_update_state.str() << ", " << dimensions_.str() << "\n";

}
void fluid_cell::send_contents(double velocity, double delta_t) {
    bool go_backwards = false;
    if (velocity < 0) go_backwards = true;

    double volume_displaced = dimensions_.area * velocity * delta_t;
    double volume_sum = 0;
    std::shared_ptr<fluid_cell> root_cell = shared_from_this();
    std::shared_ptr<fluid_cell> next_cell = nullptr;

    while (true) {
        next_cell = root_cell->neighbors_high[0];
        if (go_backwards) next_cell = root_cell->neighbors_low[0];

        volume_sum += next_cell->dimensions_.volume();

        if (volume_sum > volume_displaced) break;
        root_cell = next_cell;
    }

    double old_volume_sum = volume_sum - next_cell->dimensions_.volume();
    double fraction_in_next_cell = (volume_displaced - old_volume_sum) / (volume_sum - old_volume_sum);
    double fraction_in_root_cell = 1 - fraction_in_next_cell;

    root_cell->state_ += pre_update_state * fraction_in_root_cell;
    next_cell->state_ += pre_update_state * fraction_in_next_cell;
}
