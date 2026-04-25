
#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <iostream> // 输入输出
#include <iomanip>  // 控制输出格式
#include <cmath>    // 数学函数
#include <stdexcept> // 异常处理

namespace sjtu {

class divided_by_zero final : public std::exception {
  public:
    divided_by_zero() = default;
    ~divided_by_zero() = default;
    const char* what() const noexcept override {
        return "complex divided by zero!";
    }
};

inline int sign(double x) {
    const double eps = 1e-6;
    return (x > eps) - (x < -eps);
}

class complex {
  private:
    double a, b; // a + bi
  public:
    complex() : a(0), b(0) {}
    complex(double a) : a(a), b(0) {}
    complex(double a, double b) : a(a), b(b) {}

    double &real() { return a; }
    double &imag() { return b; }
    const double &real() const { return a; }
    const double &imag() const { return b; }

    complex operator - () const {
        return complex(-a, -b);
    }
    complex operator ~ () const {
        return complex(a, -b);
    }

    complex operator + (const complex &rhs) const {
        return complex(a + rhs.a, b + rhs.b);
    }
    complex operator - (const complex &rhs) const {
        return complex(a - rhs.a, b - rhs.b);
    }
    complex operator * (const complex &rhs) const {
        return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
    }
    complex operator / (const complex &rhs) const {
        if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
            throw divided_by_zero();
        }
        double den = rhs.a * rhs.a + rhs.b * rhs.b;
        return complex((a * rhs.a + b * rhs.b) / den, (b * rhs.a - a * rhs.b) / den);
    }

    complex &operator += (const complex &rhs) {
        a += rhs.a;
        b += rhs.b;
        return *this;
    }
    complex &operator -= (const complex &rhs) {
        a -= rhs.a;
        b -= rhs.b;
        return *this;
    }
    complex &operator *= (const complex &rhs) {
        double new_a = a * rhs.a - b * rhs.b;
        double new_b = a * rhs.b + b * rhs.a;
        a = new_a;
        b = new_b;
        return *this;
    }
    complex &operator /= (const complex &rhs) {
        if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
            throw divided_by_zero();
        }
        double den = rhs.a * rhs.a + rhs.b * rhs.b;
        double new_a = (a * rhs.a + b * rhs.b) / den;
        double new_b = (b * rhs.a - a * rhs.b) / den;
        a = new_a;
        b = new_b;
        return *this;
    }

    bool operator == (const complex &rhs) const {
        return sign(a - rhs.a) == 0 && sign(b - rhs.b) == 0;
    }
    
    explicit operator bool() const {
        return sign(a) != 0 || sign(b) != 0;
    }

    friend std::ostream &operator << (std::ostream &os, const complex &x) {
        if (sign(x.a) == 0) os << std::fixed << std::setprecision(6) << 0.0;
        else os << std::fixed << std::setprecision(6) << x.a;

        if (sign(x.b) < 0) os << "-" << std::fixed << std::setprecision(6) << std::abs(x.b) << "i";
        else os << "+" << std::fixed << std::setprecision(6) << std::abs(x.b) << "i";
        return os;
    }
};

}

#endif
