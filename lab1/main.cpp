#include <iostream>
#include "gcd.h"

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << lab1::gcd(a, b) << std::endl;
    return 0;
}