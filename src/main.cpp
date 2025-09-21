#include "fluid/fluid_cell.hpp"
#include "fluid/fluid_system.hpp"

// currently one-dimensional

int main() {
    fluid_system fluid_system_;
    for (int i = 0; i < 100; i++) {
        fluid_cell c = fluid_cell(
            fluid_cell::dimensions{i*0.1, 1.0},
            fluid_cell::state()
        );
        fluid_system_.add_cell(c);
    }
    fluid_system_.update();
    std::cout << "hello world\n";
}