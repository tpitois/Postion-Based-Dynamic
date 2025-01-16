//
// Created by pits on 11/01/25.
//

#include "Plane.h"

#include <algorithm>

Plane::Plane(Vec2 pos, Vec2 normal): pos(pos), normal(normal) {
    this->normal = normalize(normal);
}

std::ostream &operator<<(std::ostream &os, const Plane &plane) {
    os << plane.pos << " " << plane.normal;
    return os;
}

Line Plane::toLine(double width, double height) const {
    Vec2 direction = {-normal.y, normal.x};

    double max_dim = 1.5 * std::max(width, height);

    Vec2 p1 = pos+direction*max_dim;
    Vec2 p2 = pos-direction*max_dim;

    return {p1, p2};
};
