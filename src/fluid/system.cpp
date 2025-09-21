#include <sstream>
#include <limits>
#include <math.h>
#include "system.hpp"

namespace fluid {

system::system(double delta_t_) {
    delta_t = delta_t_;
}
void system::update() {
    std::vector<cell> cells_original;
    for (std::shared_ptr<cell> c : cells) c->set_pre_update_state();
    for (std::shared_ptr<cell> c : cells) c->update(delta_t);
}
void system::add_cell(cell c, std::vector<std::shared_ptr<cell>> attach_low, std::vector<std::shared_ptr<cell>> attach_high) {
    c.neighbors_low = attach_low;
    c.neighbors_high = attach_high;
    cells.push_back(std::make_shared<cell>(c));
}
void system::add_cell(cell c) {
    if (cells.size() == 0) add_cell(c, {}, {});
    add_cell(c, {cells.back()}, {});
}
bool system::valid_index(size_t index) {
    if (index < 0) return false;
    if (index >= cells.size()) return false;
    return true;
}
std::string system::str() {
    std::ostringstream output;
    std::string characters = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
    double minimum = std::numeric_limits<double>::max();
    double maximum = std::numeric_limits<double>::lowest();
    for (std::shared_ptr<cell>& c : cells) minimum = fmin(c->state_.velocity(), minimum);
    for (std::shared_ptr<cell>& c : cells) maximum = fmax(c->state_.velocity(), maximum);
    //output << "max: " << maximum << "\n";
    //output << "min: " << minimum << "\n";
    for (std::shared_ptr<cell>& c : cells) {
        double fraction;
        if (maximum - minimum < std::numeric_limits<double>::epsilon()) fraction = 0.0;
        else fraction = (c->state_.velocity() - minimum) / (maximum - minimum);
        
        //output << fraction;
        output << characters[floor(fraction * (characters.size() - 1))];
    }
    return output.str();
}

}