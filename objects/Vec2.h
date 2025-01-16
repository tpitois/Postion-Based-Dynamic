//
// Created by pits on 11/01/25.
//

#ifndef VEC2_H
#define VEC2_H
#include <ostream>


class Vec2 {
public:
    double x;
    double y;

    Vec2(double x, double y): x(x), y(y) {};
    friend std::ostream &operator<<(std::ostream &os, const Vec2 &u);
    bool operator==(const Vec2 &other) const {return x == other.x && y == other.y;};
    Vec2 operator+=(const Vec2 &other);
    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator*(double scalar) const;
    Vec2 operator/(double scalar) const;
    [[nodiscard]] double norm() const;
};

double dot(const Vec2 &u, const Vec2 &v);
Vec2 normalize(const Vec2 &u);


#endif //VEC2_H
