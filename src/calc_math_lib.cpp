#include "calc_math_lib.hpp"

namespace mathlib {

ErrorCode check_result(double r) {
    if (r > DBL_MAX || r < -DBL_MAX) {
        return ErrorCode::TYPE_OVERFLOW;
    }
    return ErrorCode::OK;
}

ErrorCode add(MathResult &result) {
    result.op = MathOperation::ADD;

    result.res = static_cast<double>(result.x) + static_cast<double>(result.y);
    return check_result(result.res);
}

ErrorCode sub(MathResult &result) {
    result.op = MathOperation::SUB;

    result.res = static_cast<double>(result.x) - static_cast<double>(result.y);
    return check_result(result.res);
}

ErrorCode mul(MathResult &result) {
    result.op = MathOperation::MUL;

    result.res = static_cast<double>(result.x) * static_cast<double>(result.y);
    return check_result(result.res);
}

ErrorCode div(MathResult &result) {
    result.op = MathOperation::DIV;

    if (result.y == 0L) {
        return ErrorCode::DIVISION_BY_ZERO;
    }

    result.res = static_cast<double>(result.x) / static_cast<double>(result.y);
    return check_result(result.res);
}

ErrorCode pow(MathResult &result) {
    result.op = MathOperation::POW;

    if (result.y == 0L) {
        result.res = 1.0;
        return ErrorCode::OK;
    }

    if (result.x == 0L) {
        if (result.y < 0L) {
            return ErrorCode::DIVISION_BY_ZERO;
        }
        result.res = 0.0;
        return ErrorCode::OK;
    }

    double r = 1.0;
    const std::int64_t exp = (result.y < 0L) ? -result.y : result.y;

    for (int64_t i = 0L; i < exp; ++i) {
        r *= static_cast<double>(result.x);
        if (check_result(r) == ErrorCode::TYPE_OVERFLOW) {
            return ErrorCode::TYPE_OVERFLOW;
        }
    }

    if (result.y < 0L) {
        r = 1.0 / r;
    }

    result.res = r;

    return ErrorCode::OK;
}

ErrorCode fac(MathResult &result) {
    result.op = MathOperation::FAC;

    if (result.x < 0L) {
        return ErrorCode::FACTORIAL_OF_NEGATIVE_NUMBER;
    }

    // Assume that 170! is the upper boundary for double overflow :)
    if (result.x > static_cast<std::int64_t>(FACTORIAL_MAX_BASE)) {
        return ErrorCode::TYPE_OVERFLOW;
    }

    if ((result.x == 0L) || (result.x == 1L)) {
        result.res = 1.0;
        return ErrorCode::OK;
    }

    MathResult prev;
    prev.x = result.x;

    const ErrorCode ec = fac(prev);
    if (ec != ErrorCode::OK) {
        return ec;
    }

    result.res = static_cast<double>(result.x) * prev.res;

    return ErrorCode::OK;
}

} // namespace mathlib
