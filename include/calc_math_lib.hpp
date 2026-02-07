#pragma once

#include <cstdint>

namespace mathlib {

constexpr double DBL_MAX = 1e308;
constexpr std::int64_t FACTORIAL_MAX_BASE = 20;

enum class ErrorCode : std::uint8_t {
    NONE,
    OK,
    DIVISION_BY_ZERO,
    FACTORIAL_OF_NEGATIVE_NUMBER,
    TYPE_OVERFLOW
};

static ErrorCode check_double(double r);
const char *err_to_str(ErrorCode ec);

ErrorCode add(std::int64_t x, std::int64_t y, std::int64_t &res);
ErrorCode sub(std::int64_t x, std::int64_t y, std::int64_t &res);
ErrorCode mul(std::int64_t x, std::int64_t y, std::int64_t &res);
ErrorCode div(std::int64_t x, std::int64_t y, double &res);
ErrorCode pow(std::int64_t x, std::int64_t y, double &res);
ErrorCode fac(std::int64_t x, std::int64_t &res);

} // namespace mathlib
