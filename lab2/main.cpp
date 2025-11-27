#include <iostream>
#include "include/decimal.hpp"

int main() {
    Decimal a("123");
    Decimal b("877");

    std::cout << "a = " << a.toString() << "\n";
    std::cout << "b = " << b.toString() << "\n";

    Decimal sum = a.add(b);
    std::cout << "a + b = " << sum.toString() << "\n";

    Decimal diff = b.subtract(a);
    std::cout << "b - a = " << diff.toString() << "\n";

    return 0;
}