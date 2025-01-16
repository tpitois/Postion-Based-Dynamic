#ifndef CONTEXT_H
#define CONTEXT_H
#include "objects/Particle.h"
#include "objects/Plane.h"
#include "objects/Circle.h"
#include <vector>
#include <cmath>



class Context
{
public:
    Context() = default;
    ~Context() = default;

    void inverseGravity() {gravity = gravity * (-1);};
    void changeFluid(int index) {fluidViscosityIndex = index;};

    void addParticle(const Particle &particle) {vec.push_back(particle);};
    void addPlaneCollider(const Plane &plane) {planeCollider.push_back(plane);};
    void addCircleCollider(const Circle &circle) {circleCollider.push_back(circle);};


    [[nodiscard]] std::vector<Particle> const &getVec() const {return vec;};
    [[nodiscard]] std::vector<Plane> const &getPlaneCollider() const {return planeCollider;};
    [[nodiscard]] std::vector<Circle> const &getCircleCollider() const {return circleCollider;};

    void updatePhysicalSystem(float dt);
    void applyExternalForce(float dt);
    void updateExpectedPosition(float dt);

    void addDynamicContactConstraints(float dt);
    static void addPlaneStaticContactConstraints(const Plane &plane, Particle &particle);
    void addStaticContactConstraints(float dt);
    void updateVelocityAndPosition(float dt);

private:
    std::vector<Particle> vec;
    std::vector<Plane> planeCollider;
    std::vector<Circle> circleCollider;
    Vec2 gravity = {0, 9.8};
    std::vector<double> fluidViscosity = {1.8 * pow(10, -5), 1 * pow(10, -3), 6 * pow(10, -4)};
    int fluidViscosityIndex = 0;
};



#endif // CONTEXT_H
