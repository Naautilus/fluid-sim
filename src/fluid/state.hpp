#pragma once

namespace fluid {

struct state {
    double mass = 0;
    double momentum = 0;
    double thermal_energy = 0;
    double velocity();
    double temperature();
    std::string str();
    void operator+=(const state& other);
    void operator-=(const state& other);
    state operator*(const double& num);
};

}