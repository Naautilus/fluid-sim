#include "fluid_cell.hpp";

std::string fluid_cell::state::str() {
    std::ostringstream output;
    output << "m = " << mass << " kg, ";
    output << "v = " << momentum / mass << " m/s, ";
    output << "T = " << thermal_energy / mass << " K";
    return output.str();
}
void fluid_cell::state::operator+=(const state& other) {
    mass += other.mass;
    momentum += other.momentum;
    thermal_energy += other.thermal_energy;
}
void fluid_cell::state::operator-=(const state& other) {
    mass -= other.mass;
    momentum -= other.momentum;
    thermal_energy -= other.thermal_energy;
}
fluid_cell::state fluid_cell::state::operator*(const double& num) {
    state output;
    output.mass = mass * num;
    output.momentum = momentum * num;
    output.thermal_energy = thermal_energy * num;
    return output;
}