#include "calc_math_lib.hpp"

#include <stdexcept>

namespace mathlib {

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int div(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("No division by zero");
    }
    return a / b;
}

double pow(int base, int deg) {
    double res = 1.0;

    if (deg > 0) {
        for (int i = 0; i < deg; ++i) {
            res *= base;
        }
    } else if (deg < 0) {
        for (int i = 0; i > deg; --i) {
            res /= base;
        }
    }

    return res;
}

int fac(int base) {
    if (base < 0) {
        throw std::runtime_error("No factorial of negative number");
    }
    if (base <= 1) {
        return 1;
    }
    return base * fac(base - 1);
}

} // namespace mathlib
