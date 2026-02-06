#include "calc_math_lib.hpp"

namespace mathlib {

ErrorCode check_result(double r) {
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

ErrorCode add(std::int64_t x, std::int64_t y, double &res) {
    res = static_cast<double>(x) + static_cast<double>(y);
    return check_result(res);
}

ErrorCode sub(std::int64_t x, std::int64_t y, double &res) {
    res = static_cast<double>(x) - static_cast<double>(y);
    return check_result(res);
}

ErrorCode mul(std::int64_t x, std::int64_t y, double &res) {
    res = static_cast<double>(x) * static_cast<double>(y);
    return check_result(res);
}

ErrorCode div(std::int64_t x, std::int64_t y, double &res) {
    if (y == 0L) {
        return ErrorCode::DIVISION_BY_ZERO;
    }

    res = static_cast<double>(x) / static_cast<double>(y);
    return check_result(res);
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
        if (check_result(r) == ErrorCode::TYPE_OVERFLOW) {
            return ErrorCode::TYPE_OVERFLOW;
        }
    }

    if (y < 0L) {
        r = 1.0 / r;
    }

    res = r;

    return ErrorCode::OK;
}

ErrorCode fac(std::int64_t x, double &res) {
    if (x < 0L) {
        return ErrorCode::FACTORIAL_OF_NEGATIVE_NUMBER;
    }

    // Assume that 170! is the upper boundary for double overflow :)
    if (x > static_cast<std::int64_t>(FACTORIAL_MAX_BASE)) {
        return ErrorCode::TYPE_OVERFLOW;
    }

    if ((x == 0L) || (x == 1L)) {
        res = 1.0;
        return ErrorCode::OK;
    }

    auto prev_res = 0.0;
    const ErrorCode ec = fac(x - 1, prev_res);
    if (ec != ErrorCode::OK) {
        return ec;
    }

    res = static_cast<double>(x) * prev_res;

    return ErrorCode::OK;
}

} // namespace mathlib
