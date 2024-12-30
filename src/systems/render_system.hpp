#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../entity/ecs_manager.hpp"

// Handle the rendering of entities that have a RenderComponent and a TransformComponent
class RenderSystem {
public:
    RenderSystem() = default;
    RenderSystem(const unsigned int shader, GLFWwindow* window);

    // Update entities that have a RenderComponent and a TransformComponent
    void update(ECSManager &ecs);

private:
    GLFWwindow* window;
    unsigned int model_loc;
};