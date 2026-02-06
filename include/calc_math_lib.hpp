#pragma once

#include <cstdint>

namespace mathlib {

constexpr double DBL_MAX = 1e308;
constexpr std::uint8_t FACTORIAL_MAX_BASE = 170;

enum class ErrorCode : std::uint8_t {
    NONE,
    OK,
    DIVISION_BY_ZERO,
    FACTORIAL_OF_NEGATIVE_NUMBER,
    TYPE_OVERFLOW
};

static ErrorCode check_result(double r);
const char *err_to_str(ErrorCode ec);

ErrorCode add(std::int64_t x, std::int64_t y, double &res);
ErrorCode sub(std::int64_t x, std::int64_t y, double &res);
ErrorCode mul(std::int64_t x, std::int64_t y, double &res);
ErrorCode div(std::int64_t x, std::int64_t y, double &res);
ErrorCode pow(std::int64_t x, std::int64_t y, double &res);
ErrorCode fac(std::int64_t x, double &res);

} // namespace mathlib
