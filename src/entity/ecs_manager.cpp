#include "ecs_manager.hpp"

// Create an entity and return its id
[[nodiscard]] unsigned int ECSManager::create_entity()
{
    unsigned int entity_id = entity_count;
    entity_masks[entity_id] = 0;
    entity_count++;
    return entity_id;
}

// Add a PhysicsComponent to an entity
void ECSManager::add_component(const unsigned int entity, const PhysicsComponent &component)
{
    physics_components[entity] = component;
    entity_masks[entity] |= static_cast<unsigned int>(ComponentType::PHYSICS);
}

// Add a TransformComponent to an entity
void ECSManager::add_component(const unsigned int entity, const TransformComponent &component)
{
    transform_components[entity] = component;
    entity_masks[entity] |= static_cast<unsigned int>(ComponentType::TRANSFORM);
}

// Add a RenderComponent to an entity
void ECSManager::add_component(const unsigned int entity, const RenderComponent &component)
{
    render_components[entity] = component;
    entity_masks[entity] |= static_cast<unsigned int>(ComponentType::RENDER);
}

// Add a CameraComponent to an entity
void ECSManager::add_component(const unsigned int entity, const CameraComponent &component)
{
    camera_component.first = entity;
    camera_component.second = component;
    entity_masks[entity] |= static_cast<unsigned int>(ComponentType::CAMERA);
}

// Remove a component from an entity
void ECSManager::remove_component(const unsigned int entity, const ComponentType &component)
{
    switch (component)
    {
    case ComponentType::TRANSFORM:
    {
        auto it = transform_components.find(entity);
        if (it != transform_components.end())
            transform_components.erase(it);
        break;
    }
    case ComponentType::PHYSICS:
    {
        auto it = physics_components.find(entity);
        if (it != physics_components.end())
            physics_components.erase(it);
        break;
    }
    case ComponentType::RENDER:
    {
        auto it = render_components.find(entity);
        if (it != render_components.end())
            render_components.erase(it);
        break;
    }
    case ComponentType::CAMERA:
    {
        std::cout << "[ECS MANAGER WARNING]\n"
                  << "CameraComponent removal not implemented\n";
        break;
    }
    default:
        std::cerr << "[ECS MANAGER ERROR]\n"
                  << "Unknown component type for removal\n";
        break;
    }
}

// Get the entity mask
[[nodiscard]] unsigned int ECSManager::get_entity_mask(const unsigned int entity) const
{
    return entity_masks.at(entity);
}

// Get entities masks
[[nodiscard]] std::unordered_map<unsigned int, unsigned int> ECSManager::get_masks() const
{
    return entity_masks;
}

// Get physics components
[[nodiscard]] std::unordered_map<unsigned int, PhysicsComponent> &ECSManager::get_physics()
{
    return physics_components;
}

// Get transform components
[[nodiscard]] std::unordered_map<unsigned int, TransformComponent> &ECSManager::get_transforms()
{
    return transform_components;
}

// Get render components
[[nodiscard]] std::unordered_map<unsigned int, RenderComponent> &ECSManager::get_renders()
{
    return render_components;
}

// Get camera component
[[nodiscard]] std::pair<unsigned int, CameraComponent> &ECSManager::get_camera()
{
    return camera_component;
}
