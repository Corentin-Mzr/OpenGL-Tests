#pragma once

#include <glm/glm.hpp>

struct TransformComponent
{
    glm::vec3 position, euler;
    float scale;
    TransformComponent(const glm::vec3 &pos = {0.0f, 0.0f, 0.0f},
                       const glm::vec3 &euler = {0.0f, 0.0f, 0.0f},
                       const float scale = 1.0f) : position(pos), euler(euler), scale(scale)
    {
    }
};