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
    std::shared_ptr<cell> c_shared = std::make_shared<cell>(c);
    cells.push_back(c_shared);

    for (std::shared_ptr<cell> other : attach_low) other->neighbors_high.push_back(c_shared);
    for (std::shared_ptr<cell> other : attach_high) other->neighbors_low.push_back(c_shared);
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

std::vector<double> _str_values(std::vector<std::shared_ptr<cell>> cells) {
    std::vector<double> values;
    for (std::shared_ptr<cell>& c : cells) values.push_back(c->state_.mass);
    return values;
}

std::string system::str(double minimum, double maximum) {
    auto values = _str_values(cells);

    std::ostringstream output;
    std::string characters = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
    std::vector<double> brightness = {0.0000, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417, 0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747, 0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382, 0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881, 0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972, 0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039, 0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 0.9999};
    double gamma = 1.6;

    for (double value : values) {
        double fraction;
        if (maximum - minimum < std::numeric_limits<double>::epsilon()) fraction = 0.0;
        else fraction = (value - minimum) / (maximum - minimum);

        fraction = pow(fraction, 1.0 / gamma);
        
        char closest_character;
        double lowest_brightness_error = 1.0;

        for (int i = 0; i < brightness.size(); i++) {
            double brightness_error = fabs(fraction - brightness[i]);
            if (brightness_error < lowest_brightness_error) {
                lowest_brightness_error = brightness_error;
                closest_character = characters[i];
            }
        }
        output << closest_character;
    }
    output << "(" << minimum << " to " << maximum << ")";
    return output.str();
}

std::string system::str() {
    auto values = _str_values(cells);
    double minimum = std::numeric_limits<double>::max();
    double maximum = std::numeric_limits<double>::lowest();
    for (double value : values) minimum = fmin(value, minimum);
    for (double value : values) maximum = fmax(value, maximum);
    return str(minimum, maximum);
}

}