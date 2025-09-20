#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <format>
#include <sstream>

// currently one-dimensional

struct fluid_cell {
    struct state {
        double pressure = 0;
        double density = 0;
        double velocity = 0;
        double temperature = 0;
        std::string str() {
            std::ostringstream output;
            output << "P = " << pressure << " pa, ";
            output << "p = " << density << " kg/m^3, ";
            output << "v = " << velocity << " m/s, ";
            output << "T = " << temperature << " K";
            return output.str();
        }
    };
    struct dimensions {
        double area = 0;
        double length = 0;
        std::string str() {
            std::ostringstream output;
            output << "area = " << area << " m^2, ";
            output << "length = " << length << " m";
            return output.str();
        }
    };
    dimensions dimensions_;
    state state_, pre_update_state;
    std::vector<size_t> neighbors_low, neighbors_high;
    fluid_cell(dimensions dimensions__, state state__) {
        dimensions_ = dimensions__;
        state_ = state__;
    }
    void set_pre_update_state() {
        pre_update_state = state_;
    }
    void update() {
        std::cout << "cell " << this << " updating: " << state_.str() << ", " << dimensions_.str() << "\n";
    }
};

struct fluid_system {
    std::vector<fluid_cell> cells;
    void update() {
        std::vector<fluid_cell> cells_original;
        for (fluid_cell& c : cells) c.set_pre_update_state();
        for (fluid_cell& c : cells) c.update();
    }
    void add_cell(fluid_cell c, std::vector<size_t> attach_low, std::vector<size_t> attach_high) {
        c.neighbors_low = attach_low;
        c.neighbors_high = attach_high;
        cells.push_back(c);
    }
    void add_cell(fluid_cell c) {
        add_cell(c, {cells.size() - 1}, {});
    }
};

int main() {
    fluid_system fluid_system_;
    for (int i = 0; i < 100; i++) {
        fluid_system_.add_cell(fluid_cell(
            fluid_cell::dimensions{i*1.0, 0.0},
            fluid_cell::state()
        ));
    }
    fluid_system_.update();
    std::cout << "hello world\n";
}