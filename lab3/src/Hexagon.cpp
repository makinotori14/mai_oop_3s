#include "Hexagon.h"
#include <cmath>
#include <stdexcept>

Hexagon::Hexagon() {
    double side = 1.0;
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        double x = side * cos(angle);
        double y = side * sin(angle);
        vertices.emplace_back(x, y);
    }
}

Hexagon::Hexagon(const std::vector<std::pair<double, double>>& verts) {
    if (verts.size() != 6) {
        throw std::invalid_argument("Hexagon must have exactly 6 vertices");
    }
    vertices = verts;
}

const std::vector<std::pair<double, double>>& Hexagon::getVertices() const {
    return vertices;
}

double Hexagon::getArea() const {
    double area = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[j].first * vertices[i].second;
    }
    return std::abs(area) / 2.0;
}

std::pair<double, double> Hexagon::getCenter() const {
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

bool Hexagon::operator==(const Figure& other) const {
    const Hexagon* otherHex = dynamic_cast<const Hexagon*>(&other);
    if (!otherHex) return false;

    if (vertices.size() != otherHex->vertices.size()) return false;

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (std::abs(vertices[i].first - otherHex->vertices[i].first) > 1e-9 ||
            std::abs(vertices[i].second - otherHex->vertices[i].second) > 1e-9) {
            return false;
        }
    }
    return true;
}

Figure& Hexagon::operator=(const Figure& other) {
    if (this == &other) return *this;

    const Hexagon* otherHex = dynamic_cast<const Hexagon*>(&other);
    if (!otherHex) {
        throw std::invalid_argument("Cannot assign different figure type to Hexagon");
    }

    vertices = otherHex->vertices;
    return *this;
}

Figure& Hexagon::operator=(Figure&& other) {
    if (this == &other) return *this;

    Hexagon* otherHex = dynamic_cast<Hexagon*>(&other);
    if (!otherHex) {
        throw std::invalid_argument("Cannot move-assign different figure type to Hexagon");
    }

    vertices = std::move(otherHex->vertices);
    return *this;
}

Hexagon::operator double() const {
    return getArea();
}