#pragma once

#include <glm/glm.hpp>

struct CameraComponent
{
    glm::vec3 right, up, forward;
    CameraComponent(const glm::vec3 &right = {0.0f, 0.0f, 0.0f},
                    const glm::vec3 &up = {0.0f, 0.0f, 0.0f},
                    const glm::vec3 &forward = {0.0f, 0.0f, 0.0f}) : right(right), up(up), forward(forward)
    {
    }
};