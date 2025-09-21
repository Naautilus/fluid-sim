#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <format>
#include "dimensions.hpp"
#include "state.hpp"

namespace fluid {

struct cell : std::enable_shared_from_this<cell> {
    dimensions dimensions_;
    state state_, pre_update_state;
    std::vector<std::shared_ptr<cell>> neighbors_low, neighbors_high;
    cell(dimensions dimensions__, state state__);
    void set_pre_update_state();
    void update(double delta_t);
    void send_contents(double velocity, double delta_t);
};

}