#include "fluid/cell.hpp"
#include "fluid/system.hpp"

// currently one-dimensional

int main() {
    fluid::system system_(1.0);
    for (int i = 0; i < 100; i++) {
        fluid::cell c = fluid::cell(
            fluid::dimensions{1.0, 1.0},
            fluid::state()
        );
        system_.add_cell(c);
    }
    system_.cells[0]->state_ = fluid::state{1.0, 2.0, 0.0};
    system_.cells[99]->state_ = fluid::state{1.0, -2.0, 0.0};
    std::cout << system_.str(0.0, 1.0) << "\n";
    for (int i = 0; i < 100; i++) {
        system_.update();
        std::cout << system_.str(0.0, 1.0) << "\n";
    }
    std::cout << "hello world\n";
}