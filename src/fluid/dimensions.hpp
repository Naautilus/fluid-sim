#pragma once
#include <string>

namespace fluid {

struct dimensions {
    double area = 0;
    double length = 0;
    double volume();
    std::string str();
};

}