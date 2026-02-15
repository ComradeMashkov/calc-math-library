#pragma once

#include <cstdint>
#include <stdexcept>

namespace mathlib {

class Utils {
  public:
    static bool check_double(double r);
    static constexpr double DBL_MAX = 1e308;
    static constexpr std::int64_t FACTORIAL_MAX_BASE = 20;
};

class DblMath;

class IntMath {
  public:
    explicit IntMath(std::int64_t val = 0L) : val_(val) {}

    std::int64_t value() const;

    IntMath add(const IntMath &rhs) const;
    IntMath sub(const IntMath &rhs) const;
    IntMath mul(const IntMath &rhs) const;

    DblMath div(const IntMath &rhs) const;
    DblMath pow(const IntMath &rhs) const;

    IntMath fac() const;

  private:
    std::int64_t val_;
};

class DblMath {
  public:
    explicit DblMath(double val = 0.0) : val_(val) {}

    // double value() const;

  private:
    double val_;
};

} // namespace mathlib
