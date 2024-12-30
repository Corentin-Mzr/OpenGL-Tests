#pragma once

#include "entity/ecs_manager.hpp"

// Handle the physics of entities that have a PhysicsComponent and a TransformComponent
class PhysicsSystem
{
public:
    // Update entities that have a PhysicsComponent and a TransformComponent
    void update(ECSManager &ecs,
                const float dt);
};