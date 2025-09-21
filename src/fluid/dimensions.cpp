#include "fluid_cell.hpp";

double fluid_cell::dimensions::volume() {
    return area * length;
}
std::string fluid_cell::dimensions::str() {
    std::ostringstream output;
    output << "area = " << area << " m^2, ";
    output << "length = " << length << " m";
    return output.str();
}