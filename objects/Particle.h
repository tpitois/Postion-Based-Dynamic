#ifndef PARTICLE_H
#define PARTICLE_H
#include <QColor>

#include "Vec2.h"

struct Particle {
    Vec2 pos;
    Vec2 expectedPos;
    Vec2 velocity;
    double mass;
    double radius;
    double inverseMass;
    QColor color;
    Particle(): pos({0, 0}), expectedPos(0, 0), velocity(0, 0), mass(1), radius(20), inverseMass(1), color(Qt::green) {};
    void setMass(double m) {
        mass = m;
        inverseMass = 1 / m;
    }
};


#endif // PARTICLE_H
