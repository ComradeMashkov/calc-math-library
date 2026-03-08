#pragma once

#include <cstdint>
#include <limits>
#include <stdexcept>

namespace mathlib {

class Utils {
  public:
    static bool check_double(double r);
    static constexpr double DBL_MAX = std::numeric_limits<double>::max();
    static constexpr std::int64_t FACTORIAL_MAX_BASE = 20;
};

class DblMath;

class IntMath {
  public:
    explicit IntMath(std::int64_t val = 0L) : val_(val) {}

    std::int64_t value() const;
    void set(std::int64_t val);

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

    double value() const;
    void set(double val);

  private:
    double val_;
};

} // namespace mathlib
