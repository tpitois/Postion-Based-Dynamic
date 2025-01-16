#include "context.h"

void Context::updatePhysicalSystem(float dt) {
    applyExternalForce(dt);
    updateExpectedPosition(dt);
    addDynamicContactConstraints(dt);
    addStaticContactConstraints(dt);
    updateVelocityAndPosition(dt);
}

void Context::applyExternalForce(float dt) {
    double viscosity = fluidViscosity[fluidViscosityIndex];
    for (auto &particle: vec) {
        Vec2 smooth_friction = particle.velocity * (particle.velocity.norm() * viscosity / 3.141592) * particle.radius * particle.radius * (-1);
        particle.velocity += gravity * dt + smooth_friction * particle.inverseMass * dt;
    }
}

void Context::updateExpectedPosition(float dt) {
    for (auto &particle: vec) {
        particle.expectedPos = particle.pos + particle.velocity * dt;
    }
}
void Context::addDynamicContactConstraints(float dt) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < i; j++) {
            Vec2 x = vec[i].expectedPos - vec[j].expectedPos;
            double x_norm = x.norm();
            double C = x_norm - (vec[i].radius + vec[j].radius);
            if (C < 0) {
                double sumInverseMass = vec[i].inverseMass + vec[j].inverseMass;
                double sigma_i = C * vec[i].inverseMass / sumInverseMass;
                double sigma_j = C * vec[j].inverseMass / sumInverseMass;
                Vec2 delta_i = x * (-sigma_i) / x_norm;
                Vec2 delta_j = x * sigma_j / x_norm;
                vec[i].expectedPos += delta_i;
                vec[j].expectedPos += delta_j;
            }
        }
    }
}

void Context::addPlaneStaticContactConstraints(const Plane &plane, Particle &particle) {
    double dotProduct = dot(particle.expectedPos - plane.getPos(), plane.getNormal());
    Vec2 particleProjection = particle.expectedPos - plane.getNormal() * dotProduct;
    double C = dot(particle.expectedPos - particleProjection, plane.getNormal()) - particle.radius;
    Vec2 delta = plane.getNormal()  * (-C);
    particle.expectedPos += delta * 2;
}

void Context::addStaticContactConstraints(float dt) {
    for (auto &particle: vec) {
        for (const auto &plane: planeCollider) {
            if (dot(particle.expectedPos - plane.getPos(), plane.getNormal()) - particle.radius < 0) {
                addPlaneStaticContactConstraints(plane, particle);
            }
        }

        for (const auto &circle: circleCollider) {
            double sdf = (particle.expectedPos - circle.center).norm() - circle.radius;
            if (sdf - particle.radius < 0) {
                Vec2 normal = normalize(particle.expectedPos - circle.center);
                Vec2 pos = particle.expectedPos - normal * sdf;
                addPlaneStaticContactConstraints({pos, normal}, particle);
            }
        }
    }
}

void Context::updateVelocityAndPosition(float dt) {
    for (auto &particle: vec) {
        particle.velocity = (particle.expectedPos - particle.pos) / dt;
        particle.pos = particle.expectedPos;
    }
}
