#pragma once

#include <unordered_map>
#include <iostream>

#include "../components/component_types.hpp"
#include "../components/physics_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/render_component.hpp"
#include "../components/camera_component.hpp"

// Handle entities and their components
class ECSManager
{
public:
    // Create an entity and return its id
    [[nodiscard]] unsigned int create_entity();

    // Add a PhysicsComponent to an entity
    void add_component(const unsigned int entity, const PhysicsComponent &component);

    // Add a TransformComponent to an entity
    void add_component(const unsigned int entity, const TransformComponent &component);

    // Add a RenderComponent to an entity
    void add_component(const unsigned int entity, const RenderComponent &component);

    // Add a CameraComponent to an entity
    void add_component(const unsigned int entity, const CameraComponent &component);

    // Remove a component from an entity
    void remove_component(const unsigned int entity, const ComponentType &component);

    // Get the entity mask
    [[nodiscard]] unsigned int get_entity_mask(const unsigned int entity) const;

    // Get entities masks
    [[nodiscard]] std::unordered_map<unsigned int, unsigned int> get_masks() const;

    // Get physics components
    [[nodiscard]] std::unordered_map<unsigned int, PhysicsComponent>& get_physics();

    // Get transform components
    [[nodiscard]] std::unordered_map<unsigned int, TransformComponent>& get_transforms();

    // Get render components
    [[nodiscard]] std::unordered_map<unsigned int, RenderComponent>& get_renders();

    // Get camera component
    [[nodiscard]] std::pair<unsigned int, CameraComponent>& get_camera();

private:
    std::unordered_map<unsigned int, unsigned int> entity_masks;
    std::unordered_map<unsigned int, PhysicsComponent> physics_components;
    std::unordered_map<unsigned int, TransformComponent> transform_components;
    std::unordered_map<unsigned int, RenderComponent> render_components;

    std::pair<unsigned int, CameraComponent> camera_component;

    unsigned int entity_count = 0;
};