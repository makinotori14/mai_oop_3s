#pragma once

#include "Figure.h"

class Hexagon : public Figure {
private:
    std::vector<std::pair<double, double>> vertices;

public:
    Hexagon();

    Hexagon(const std::vector<std::pair<double, double>>& verts);

    const std::vector<std::pair<double, double>>& getVertices() const;

    double getArea() const override;
    std::pair<double, double> getCenter() const override;

    bool operator==(const Figure& other) const override;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) override;

    operator double() const override;

    virtual ~Hexagon() = default;
};