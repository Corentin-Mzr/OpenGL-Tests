#include "camera_system.hpp"

void printMatrix(const glm::mat4 &mat)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            std::cout << mat[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

CameraSystem::CameraSystem(const unsigned int shader, GLFWwindow *window) : window(window)
{
    glUseProgram(shader);
    view_loc = glGetUniformLocation(shader, "view");
    view_pos_loc = glGetUniformLocation(shader, "view_pos");
}

// Update entities that have a CameraComponent and a TransformComponent
void CameraSystem::update(ECSManager &ecs, const float dt)
{
    auto &[camera_id, camera] = ecs.get_camera();
    const unsigned int mask = ecs.get_entity_mask(camera_id);
    auto &transform_components = ecs.get_transforms();

    if (mask & static_cast<unsigned int>(ComponentType::CAMERA))
    {
        glm::vec3 &pos = transform_components[camera_id].position;
        glm::vec3 &euler = transform_components[camera_id].euler;
        const float theta = glm::radians(euler.y);
        const float phi = glm::radians(euler.z);

        glm::vec3 &right = camera.right;
        glm::vec3 &up = camera.up;
        glm::vec3 &forward = camera.forward;

        forward = {
            glm::cos(theta) * glm::cos(phi),
            glm::sin(phi),
            glm::sin(theta) * glm::cos(phi),
        };
        forward = glm::normalize(forward);
        right = glm::normalize(glm::cross(forward, world_up));
        up = glm::normalize(glm::cross(right, forward));

        // Send view matrix
        glm::mat4 view = glm::lookAt(pos, pos + forward, up);
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

        // Also send camera position for lighting
        glUniform3fv(view_pos_loc, 1, glm::value_ptr(pos));

        process_mouse(euler.y, euler.z);
        process_keyboard(pos, forward, right, dt);
        xoffset = 0.0f, yoffset = 0.0f;
    }
}

void CameraSystem::process_keyboard(glm::vec3 &pos, const glm::vec3 &forward, const glm::vec3 &right, const float dt)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    glm::vec3 dpos{0.0f, 0.0f, 0.0f};
    // Front
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        dpos += forward * velocity * dt;
    // Left
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        dpos -= right * velocity * dt;
    // Back
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        dpos -= forward * velocity * dt;
    // Right
    if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS)
        dpos += right * velocity * dt;
    // Up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        dpos += world_up * velocity * dt;
    // Down 
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        dpos -= world_up * velocity * dt;

    // Sprint
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        speed_factor = 3.0f;
    else
        speed_factor = 1.0f;

    if (glm::length(dpos) > 1.0f)
        dpos = glm::normalize(dpos);
    pos += speed_factor * dpos;
}

void CameraSystem::process_mouse(float& theta, float &phi)
{
    theta += xoffset * mouse_sensivity;
    phi += yoffset * mouse_sensivity;

    if (phi > 89.0f)
        phi = 89.0f;
    if (phi < -89.0f)
        phi = -89.0f;
}

void CameraSystem::set_offset(const float xoffset, const float yoffset)
{
    this->xoffset = xoffset;
    this->yoffset = yoffset;
}