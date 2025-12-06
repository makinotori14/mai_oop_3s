#pragma once

#include <iostream>
#include <vector>
#include <memory>

class Figure {
public:
    Figure() = default;

    virtual ~Figure() = default;

    virtual double getArea() const = 0;
    virtual std::pair<double, double> getCenter() const = 0;

    virtual bool operator==(const Figure& other) const = 0;
    virtual Figure& operator=(const Figure& other) {
        return *this;
    }
    virtual Figure& operator=(Figure&& other) {
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);

    friend std::istream& operator>>(std::istream& is, Figure& fig);

    virtual operator double() const = 0;
};
