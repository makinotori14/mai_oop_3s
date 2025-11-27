#include "../include/decimal.hpp"
#include "../include/vector.hpp"
#include <algorithm>
#include <sstream>

void Decimal::validateDigit(unsigned char d) {
    if (d > 9) {
        throw std::invalid_argument("out of range");
    }
}

void Decimal::removeLeadingZeros(Vector& vec) {
    while (vec.Size() > 1 && vec[vec.Size() - 1] == 0) {
        vec.PopBack();
    }
}

Decimal Decimal::normalize(const Vector& digits) {
    Vector normalized;
    for (size_t i = 0; i < digits.Size(); ++i) {
        normalized.PushBack(digits[i]);
    }
    removeLeadingZeros(normalized);
    Decimal result;
    result.digits = std::move(normalized);
    return result;
}

Decimal::Decimal() {
    digits.PushBack(0);
}

Decimal::Decimal(const size_t& n, unsigned char t) {
    validateDigit(t);
    if (n == 0) {
        digits.PushBack(0);
    } else {
        for (size_t i = 0; i < n; ++i) {
            digits.PushBack(t);
        }
    }
    removeLeadingZeros(digits);
}

Decimal::Decimal(const std::initializer_list<unsigned char>& list) {
    for (unsigned char d : list) {
        validateDigit(d);
        digits.PushBack(d);
    }
    removeLeadingZeros(digits);
}

Decimal::Decimal(const std::string& str) {
    if (str.empty()) {
        digits.PushBack(0);
        return;
    }
    for (char c : str) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument("0-9!");
        }
        digits.PushBack(static_cast<unsigned char>(c - '0'));
    }
    std::reverse(digits.Data(), digits.Data() + digits.Size());
    removeLeadingZeros(digits);
}

Decimal::Decimal(const Decimal& other) : digits(other.digits) {}

Decimal::Decimal(Decimal&& other) noexcept : digits(std::move(other.digits)) {}

Decimal::~Decimal() noexcept = default;

Decimal Decimal::add(const Decimal& other) const {
    Vector result;
    size_t max_size = std::max(digits.Size(), other.digits.Size());
    unsigned char carry = 0;

    for (size_t i = 0; i < max_size || carry; ++i) {
        unsigned char d1 = (i < digits.Size()) ? digits[i] : 0;
        unsigned char d2 = (i < other.digits.Size()) ? other.digits[i] : 0;
        unsigned char sum = d1 + d2 + carry;
        carry = sum / 10;
        result.PushBack(sum % 10);
    }

    return normalize(result);
}

Decimal Decimal::subtract(const Decimal& other) const {
    if (*this < other) {
        throw std::invalid_argument("negative");
    }

    Vector result;
    int borrow = 0;

    for (size_t i = 0; i < digits.Size(); ++i) {
        int d1 = static_cast<int>(digits[i]) - borrow;
        int d2 = (i < other.digits.Size()) ? static_cast<int>(other.digits[i]) : 0;

        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.PushBack(static_cast<unsigned char>(d1 - d2));
    }

    return normalize(result);
}

Decimal Decimal::copy() const {
    return *this;
}

bool Decimal::operator==(const Decimal& other) const {
    if (digits.Size() != other.digits.Size()) return false;
    for (size_t i = 0; i < digits.Size(); ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Decimal::operator!=(const Decimal& other) const {
    return !(*this == other);
}

bool Decimal::operator<(const Decimal& other) const {
    if (digits.Size() != other.digits.Size()) {
        return digits.Size() < other.digits.Size();
    }
    for (size_t i = digits.Size(); i > 0; --i) {
        if (digits[i - 1] != other.digits[i - 1]) {
            return digits[i - 1] < other.digits[i - 1];
        }
    }
    return false;
}

bool Decimal::operator>(const Decimal& other) const {
    return other < *this;
}

bool Decimal::operator<=(const Decimal& other) const {
    return !(*this > other);
}

bool Decimal::operator>=(const Decimal& other) const {
    return !(*this < other);
}

size_t Decimal::size() const {
    return digits.Size();
}

unsigned char Decimal::at(size_t index) const {
    if (index >= digits.Size()) {
        throw std::out_of_range("out of range");
    }
    return digits[index];
}

std::string Decimal::toString() const {
    std::string s;
    for (size_t i = digits.Size(); i > 0; --i) {
        s += static_cast<char>('0' + digits[i - 1]);
    }
    return s;
}