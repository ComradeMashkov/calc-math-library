#include "calc_math_lib.hpp"

namespace mathlib {

bool Utils::check_double(double r) {
    return r <= Utils::DBL_MAX && r >= -Utils::DBL_MAX;
}

std::int64_t IntMath::value() const {
    return val_;
}

void IntMath::set(std::int64_t val) {
    val_ = val;
}

IntMath IntMath::add(const IntMath &rhs) const {
    if ((rhs.val_ > 0L && val_ > INT64_MAX - rhs.val_) ||
        (rhs.val_ < 0 && val_ < INT64_MIN - rhs.val_)) {
        throw std::runtime_error("Type overflow occurred");
    }

    const std::int64_t out = val_ + rhs.val_;
    return IntMath(out);
}

IntMath IntMath::sub(const IntMath &rhs) const {
    if ((rhs.val_ > 0 && val_ < INT64_MIN + rhs.val_) ||
        (rhs.val_ < 0 && val_ > INT64_MAX + rhs.val_)) {
        throw std::runtime_error("Type overflow occurred");
    }

    const std::int64_t out = val_ - rhs.val_;
    return IntMath(out);
}

IntMath IntMath::mul(const IntMath &rhs) const {
    if ((val_ == -1 && rhs.val_ == INT64_MIN) || (rhs.val_ == -1 && val_ == INT64_MIN)) {
        throw std::runtime_error("Type overflow occurred");
    }

    bool overflow = false;

    if (val_ > 0) {
        overflow = (rhs.val_ > 0) ? (val_ > INT64_MAX / rhs.val_) : (rhs.val_ < INT64_MIN / val_);
    } else {
        overflow = (rhs.val_ > 0) ? (val_ < INT64_MIN / rhs.val_) : (rhs.val_ < INT64_MAX / val_);
    }

    if (overflow) {
        throw std::runtime_error("Type overflow occurred");
    }

    const std::int64_t out = val_ * rhs.val_;
    return IntMath(out);
}

DblMath IntMath::div(const IntMath &rhs) const {
    if (rhs.val_ == 0L) {
        throw std::runtime_error("No division by zero");
    }

    const double out = static_cast<double>(val_) / static_cast<double>(rhs.val_);
    if (const bool ok = Utils::check_double(out); !ok) {
        throw std::runtime_error("Type overflow occurred");
    }
    return DblMath(out);
}

DblMath IntMath::pow(const IntMath &rhs) const {
    if (rhs.val_ == 0L) {
        return DblMath(1.0);
    }

    if (val_ == 0L) {
        if (rhs.val_ < 0L) {
            throw std::runtime_error("No division by zero");
        }
        return DblMath(0.0);
    }

    double r = 1.0;
    const std::int64_t exp = (rhs.val_ < 0L) ? -rhs.val_ : rhs.val_;

    for (int64_t i = 0L; i < exp; ++i) {
        r *= static_cast<double>(val_);
        if (const bool ok = Utils::check_double(r); !ok) {
            throw std::runtime_error("Type overflow occurred");
        }
    }

    if (rhs.val_ < 0L) {
        r = 1.0 / r;
    }

    return DblMath(r);
}

IntMath IntMath::fac() const {
    if (val_ < 0L) {
        throw std::runtime_error("No factorial of negative number");
    }

    // Assume that 20! is the upper boundary for int64 overflow :)
    if (val_ > Utils::FACTORIAL_MAX_BASE) {
        throw std::runtime_error("Type overflow occurred");
    }

    if (val_ == 0L || val_ == 1L) {
        return IntMath(1L);
    }

    const IntMath prev = IntMath(val_ - 1L).fac();
    const std::int64_t p = prev.val_;

    if (p > INT64_MAX / val_) {
        throw std::runtime_error("Type overflow occurred");
    }

    return IntMath(p * val_);
}

double DblMath::value() const {
    return val_;
}

void DblMath::set(double val) {
    val_ = val;
}

} // namespace mathlib
