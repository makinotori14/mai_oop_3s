#pragma once

#include "vector.hpp"
#include <string>
#include <stdexcept>

class Decimal {
public:
    Decimal();
    Decimal(const size_t& n, unsigned char t = 0);
    Decimal(const std::initializer_list<unsigned char>& list);
    Decimal(const std::string& str);
    Decimal(const Decimal& other);
    Decimal(Decimal&& other) noexcept;
    ~Decimal() noexcept;

    Decimal add(const Decimal& other) const;
    Decimal subtract(const Decimal& other) const;
    Decimal copy() const;

    bool operator==(const Decimal& other) const;
    bool operator!=(const Decimal& other) const;
    bool operator<(const Decimal& other) const;
    bool operator>(const Decimal& other) const;
    bool operator<=(const Decimal& other) const;
    bool operator>=(const Decimal& other) const;

    size_t size() const;
    unsigned char at(size_t index) const;
    std::string toString() const;

private:
    Vector digits;
    static void validateDigit(unsigned char d);
    static void removeLeadingZeros(Vector& vec);
    static Decimal normalize(const Vector& digits);
};