#include "Figure.h"
#include <stdexcept>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    auto center = fig.getCenter();
    os << "Center: (" << center.first << ", " << center.second << ") ";
    os << "Area: " << static_cast<double>(fig);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    throw std::runtime_error("Cannot read base Figure object directly");
}