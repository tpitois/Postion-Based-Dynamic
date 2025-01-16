//
// Created by pits on 11/01/25.
//

#include "Vec2.h"
#include <cmath>

Vec2 Vec2::operator+=(const Vec2 &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Vec2 &u) {
    os << "(" << u.x << ", " << u.y << ")";
    return os;
}

Vec2 Vec2::operator+(const Vec2 &other) const {
    return {this->x + other.x, this->y + other.y};
};

Vec2 Vec2::operator-(const Vec2 &other) const {
    return {this->x - other.x, this->y - other.y};
};

Vec2 Vec2::operator*(double scalar) const {
    return {this->x*scalar, this->y*scalar};
}

Vec2 Vec2::operator/(double scalar) const {
    return {x/scalar, y/scalar};
}

double Vec2::norm() const {
    return sqrt(x*x + y*y);
}

double dot(const Vec2 &u, const Vec2 &v) {
    return u.x * v.x + u.y * v.y;
}

Vec2 normalize(const Vec2 &u) {
    return u / u.norm();
}
