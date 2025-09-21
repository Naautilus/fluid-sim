#include <sstream>
#include "dimensions.hpp"
#include "cell.hpp"

namespace fluid {

double dimensions::volume() {
    return area * length;
}
std::string dimensions::str() {
    std::ostringstream output;
    output << "area = " << area << " m^2, ";
    output << "length = " << length << " m";
    return output.str();
}

}