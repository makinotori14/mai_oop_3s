#include "Triangle.h"
#include <cmath>
#include <stdexcept>

Triangle::Triangle() {
    vertices = {{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}};
}

Triangle::Triangle(const std::vector<std::pair<double, double>>& verts) {
    if (verts.size() != 3) {
        throw std::invalid_argument("Triangle must have exactly 3 vertices");
    }
    vertices = verts;
}

const std::vector<std::pair<double, double>>& Triangle::getVertices() const {
    return vertices;
}

double Triangle::getArea() const {
    double x1 = vertices[0].first, y1 = vertices[0].second;
    double x2 = vertices[1].first, y2 = vertices[1].second;
    double x3 = vertices[2].first, y3 = vertices[2].second;

    return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

std::pair<double, double> Triangle::getCenter() const {
    double cx = (vertices[0].first + vertices[1].first + vertices[2].first) / 3.0;
    double cy = (vertices[0].second + vertices[1].second + vertices[2].second) / 3.0;
    return {cx, cy};
}

bool Triangle::operator==(const Figure& other) const {
    const Triangle* otherTri = dynamic_cast<const Triangle*>(&other);
    if (!otherTri) return false;

    if (vertices.size() != otherTri->vertices.size()) return false;

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (std::abs(vertices[i].first - otherTri->vertices[i].first) > 1e-9 ||
            std::abs(vertices[i].second - otherTri->vertices[i].second) > 1e-9) {
            return false;
        }
    }
    return true;
}

Figure& Triangle::operator=(const Figure& other) {
    if (this == &other) return *this;

    const Triangle* otherTri = dynamic_cast<const Triangle*>(&other);
    if (!otherTri) {
        throw std::invalid_argument("Cannot assign different figure type to Triangle");
    }

    vertices = otherTri->vertices;
    return *this;
}

Figure& Triangle::operator=(Figure&& other) {
    if (this == &other) return *this;

    Triangle* otherTri = dynamic_cast<Triangle*>(&other);
    if (!otherTri) {
        throw std::invalid_argument("Cannot move-assign different figure type to Triangle");
    }

    vertices = std::move(otherTri->vertices);
    return *this;
}

Triangle::operator double() const {
    return getArea();
}