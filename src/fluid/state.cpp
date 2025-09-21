#include <sstream>
#include "dimensions.hpp"
#include "cell.hpp"

namespace fluid {

std::string state::str() {
    std::ostringstream output;
    output << "m = " << mass << " kg, ";
    output << "v = " << velocity() << " m/s, ";
    output << "T = " << temperature() << " K";
    return output.str();
}
double state::density(double volume) {
    if (volume == 0) return 0;
    return mass / volume;
}
double state::velocity() {
    if (mass == 0) return 0;
    return momentum / mass;
}
double state::temperature() {
    double SPECIFIC_HEAT_CAPACITY = 1.0;
    if (mass == 0) return 0;
    return thermal_energy / (mass * SPECIFIC_HEAT_CAPACITY);
}
double state::pressure(double volume) {
    double IDEAL_GAS_CONSTANT = 8.31446261815324;
    // ideal gas pressure equation
    return density(volume) * IDEAL_GAS_CONSTANT * temperature();
}
void state::operator+=(const state& other) {
    mass += other.mass;
    momentum += other.momentum;
    thermal_energy += other.thermal_energy;
}
void state::operator-=(const state& other) {
    mass -= other.mass;
    momentum -= other.momentum;
    thermal_energy -= other.thermal_energy;
}
state state::operator*(const double& num) {
    state output;
    output.mass = mass * num;
    output.momentum = momentum * num;
    output.thermal_energy = thermal_energy * num;
    return output;
}

}