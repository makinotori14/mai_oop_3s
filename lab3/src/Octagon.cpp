#include "Octagon.h"
#include <cmath>
#include <stdexcept>

Octagon::Octagon() {
    double side = 1.0;
    for (int i = 0; i < 8; ++i) {
        double angle = 2 * M_PI * i / 8;
        double x = side * cos(angle);
        double y = side * sin(angle);
        vertices.emplace_back(x, y);
    }
}

Octagon::Octagon(const std::vector<std::pair<double, double>>& verts) {
    if (verts.size() != 8) {
        throw std::invalid_argument("Octagon must have exactly 8 vertices");
    }
    vertices = verts;
}

const std::vector<std::pair<double, double>>& Octagon::getVertices() const {
    return vertices;
}

double Octagon::getArea() const {
    double area = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

std::pair<double, double> Octagon::getCenter() const {
    double cx = 0.0, cy = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        cx += vertices[i].first;
        cy += vertices[i].second;
    }
    cx /= n;
    cy /= n;
    return {cx, cy};
}

bool Octagon::operator==(const Figure& other) const {
    const Octagon* otherOct = dynamic_cast<const Octagon*>(&other);
    if (!otherOct) return false;

    if (vertices.size() != otherOct->vertices.size()) return false;

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (std::abs(vertices[i].first - otherOct->vertices[i].first) > 1e-9 ||
            std::abs(vertices[i].second - otherOct->vertices[i].second) > 1e-9) {
            return false;
        }
    }
    return true;
}

Figure& Octagon::operator=(const Figure& other) {
    if (this == &other) return *this;

    const Octagon* otherOct = dynamic_cast<const Octagon*>(&other);
    if (!otherOct) {
        throw std::invalid_argument("Cannot assign different figure type to Octagon");
    }

    vertices = otherOct->vertices;
    return *this;
}

Figure& Octagon::operator=(Figure&& other) {
    if (this == &other) return *this;

    Octagon* otherOct = dynamic_cast<Octagon*>(&other);
    if (!otherOct) {
        throw std::invalid_argument("Cannot move-assign different figure type to Octagon");
    }

    vertices = std::move(otherOct->vertices);
    return *this;
}

Octagon::operator double() const {
    return getArea();
}