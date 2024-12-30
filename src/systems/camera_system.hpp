#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../components/component_types.hpp"
#include "../components/camera_component.hpp"
#include "../entity/ecs_manager.hpp"

// Handle player motion
class CameraSystem
{
public:
    CameraSystem() =  default;
    CameraSystem(const unsigned int shader, GLFWwindow* window);

    // Update entities that have a CameraComponent and a TransformComponent
    void update(ECSManager &ecs, const float dt);

    // To compute camera orientation
    void set_offset(const float xoffset, const float yoffset);

private:
    GLFWwindow* window;
    unsigned int view_loc, view_pos_loc;
    float velocity = 1.0f;
    glm::vec3 world_up{0.0f, 1.0f, 0.0f};
    float xoffset = 0.0f, yoffset = 0.0f;
    float mouse_sensivity = 0.2f;
    float speed_factor = 1.0f;

    void process_keyboard(glm::vec3 &pos, const glm::vec3 &forward, const glm::vec3 &right, const float dt);
    void process_mouse(float &theta, float &phi);
};