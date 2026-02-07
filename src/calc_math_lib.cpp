#include "calc_math_lib.hpp"

namespace mathlib {

ErrorCode check_double(double r) {
    if (r > DBL_MAX || r < -DBL_MAX) {
        return ErrorCode::TYPE_OVERFLOW;
    }
    return ErrorCode::OK;
}

const char *err_to_str(ErrorCode ec) {
    switch (ec) {
    case ErrorCode::DIVISION_BY_ZERO:
        return "Division by zero cannot be executed";
    case ErrorCode::FACTORIAL_OF_NEGATIVE_NUMBER:
        return "Factorial of negative number cannot be executed";
    case ErrorCode::TYPE_OVERFLOW:
        return "Type overflow";
    default:
        return "None";
    }
}

ErrorCode add(std::int64_t x, std::int64_t y, std::int64_t &res) {
    if ((y > 0 && x > INT64_MAX - y) || (y < 0 && x < INT64_MIN - y)) {
        return ErrorCode::TYPE_OVERFLOW;
    }
    res = x + y;
    return ErrorCode::OK;
}

ErrorCode sub(std::int64_t x, std::int64_t y, std::int64_t &res) {
    if ((y > 0 && x < INT64_MIN + y) || (y < 0 && x > INT64_MAX + y)) {
        return ErrorCode::TYPE_OVERFLOW;
    }
    res = x - y;
    return ErrorCode::OK;
}

ErrorCode mul(std::int64_t x, std::int64_t y, std::int64_t &res) {
    if (x == 0 || y == 0) {
        res = 0;
        return ErrorCode::OK;
    }
    if ((x == -1 && y == INT64_MIN) || (y == -1 && x == INT64_MIN)) {
        return ErrorCode::TYPE_OVERFLOW;
    }

    bool overflow = false;

    if (x > 0) {
        overflow = (y > 0) ? (x > INT64_MAX / y) : (y < INT64_MIN / x);
    } else {
        overflow = (y > 0) ? (x < INT64_MIN / y) : (y < INT64_MAX / x);
    }

    if (overflow) {
        return ErrorCode::TYPE_OVERFLOW;
    }

    res = x * y;
    return ErrorCode::OK;
}

ErrorCode div(std::int64_t x, std::int64_t y, double &res) {
    if (y == 0L) {
        return ErrorCode::DIVISION_BY_ZERO;
    }

    res = static_cast<double>(x) / static_cast<double>(y);
    return check_double(res);
}

ErrorCode pow(std::int64_t x, std::int64_t y, double &res) {
    if (y == 0L) {
        res = 1.0;
        return ErrorCode::OK;
    }

    if (x == 0L) {
        if (y < 0L) {
            return ErrorCode::DIVISION_BY_ZERO;
        }
        res = 0.0;
        return ErrorCode::OK;
    }

    double r = 1.0;
    const std::int64_t exp = (y < 0L) ? -y : y;

    for (int64_t i = 0L; i < exp; ++i) {
        r *= static_cast<double>(x);
        if (check_double(r) == ErrorCode::TYPE_OVERFLOW) {
            return ErrorCode::TYPE_OVERFLOW;
        }
    }

    if (y < 0L) {
        r = 1.0 / r;
    }

    res = r;
    return ErrorCode::OK;
}

ErrorCode fac(std::int64_t x, std::int64_t &res) {
    if (x < 0L) {
        return ErrorCode::FACTORIAL_OF_NEGATIVE_NUMBER;
    }

    // Assume that 20! is the upper boundary for int64 overflow :)
    if (x > FACTORIAL_MAX_BASE) {
        return ErrorCode::TYPE_OVERFLOW;
    }

    if ((x == 0L) || (x == 1L)) {
        res = 1L;
        return ErrorCode::OK;
    }

    std::int64_t prev_res = 0L;
    const ErrorCode ec = fac(x - 1, prev_res);
    if (ec != ErrorCode::OK) {
        return ec;
    }

    res = x * prev_res;
    return ErrorCode::OK;
}

} // namespace mathlib
