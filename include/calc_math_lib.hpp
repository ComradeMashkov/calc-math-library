#pragma once

#include <cstdint>

namespace mathlib {

constexpr double DBL_MAX = 1e308;
constexpr std::uint8_t FACTORIAL_MAX_BASE = 170;

enum class ErrorCode : std::uint8_t {
    OK,
    DIVISION_BY_ZERO,
    FACTORIAL_OF_NEGATIVE_NUMBER,
    TYPE_OVERFLOW
};

enum class MathOperation : std::uint8_t { NONE, ADD, SUB, MUL, DIV, POW, FAC };

struct MathResult {
    std::int64_t x = 0L;
    std::int64_t y = 0L;
    MathOperation op = MathOperation::NONE;
    double res = 0.0;
};

static ErrorCode check_result(double r);

ErrorCode add(MathResult &result);
ErrorCode sub(MathResult &result);
ErrorCode mul(MathResult &result);
ErrorCode div(MathResult &result);
ErrorCode pow(MathResult &result);

} // namespace mathlib
