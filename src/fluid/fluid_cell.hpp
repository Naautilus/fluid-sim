#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <format>
#include <sstream>

struct fluid_system;

struct fluid_cell : std::enable_shared_from_this<fluid_cell> {
    struct state {
        double mass = 0;
        double momentum = 0;
        double thermal_energy = 0;
        std::string str();
        void operator+=(const state& other);
        void operator-=(const state& other);
        state operator*(const double& num);
    };
    struct dimensions {
        double area = 0;
        double length = 0;
        double volume();
        std::string str();
    };
    dimensions dimensions_;
    state state_, pre_update_state;
    std::vector<std::shared_ptr<fluid_cell>> neighbors_low, neighbors_high;
    fluid_cell(dimensions dimensions__, state state__);
    void set_pre_update_state();
    void update(double delta_t);
    void send_contents(double velocity, double delta_t);
};
