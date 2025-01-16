//
// Created by pits on 11/01/25.
//

#ifndef PLANE_H
#define PLANE_H

#include "Vec2.h"
#include "Line.h"

class Plane {
private:
    Vec2 pos;
    Vec2 normal;

public:
    Plane(Vec2 pos, Vec2 normal);
    friend std::ostream &operator<<(std::ostream &os, const Plane &plane);
    [[nodiscard]] Vec2 const &getPos() const {return pos;};
    [[nodiscard]] Vec2 const &getNormal() const {return normal;};
    [[nodiscard]] Line toLine(double width, double height) const;
};



#endif //PLANE_H
