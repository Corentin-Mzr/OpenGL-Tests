#include "physics_system.hpp"

// Update entities that have a PhysicsComponent and a TransformComponent
void PhysicsSystem::update(ECSManager &ecs,
                           const float dt)
{
    auto &physics_components = ecs.get_physics();
    auto &transform_components = ecs.get_transforms();
    for (const auto& [entity, mask]: ecs.get_masks())
    {
        // Check for PhysicsComponent and TransformComponent
        if ((mask & static_cast<unsigned int>(ComponentType::TRANSFORM)) &&
        mask & static_cast<unsigned int>(ComponentType::PHYSICS))
        {
            transform_components[entity].position += physics_components[entity].velocity * dt;
            transform_components[entity].euler += physics_components[entity].euler_velocity * dt;

            if (transform_components[entity].euler.z > 360)
                transform_components[entity].euler.z -= 360;
        }
    }
}