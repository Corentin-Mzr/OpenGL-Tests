#pragma once

#include <glm/glm.hpp>

struct PhysicsComponent
{
    glm::vec3 velocity, euler_velocity;
    PhysicsComponent(const glm::vec3 &vel = {0.0f, 0.0f, 0.0f},
                     const glm::vec3 &euler_vel = {0.0f, 0.0f, 0.0f}) : velocity(vel), euler_velocity(euler_vel)
    {
    }
};