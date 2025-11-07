#include "gcd.h"

namespace lab1 {

int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (a > 0) {
        b %= a;
        std::swap(a, b);
    }
    return b;
}

}