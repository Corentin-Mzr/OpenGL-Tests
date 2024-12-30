#pragma once

#include <string>
#include <stdexcept>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../view/shader.hpp"

#include "../meshes/square_mesh.hpp"
#include "../meshes/material.hpp"
#include "../meshes/cube_mesh.hpp"
#include "../meshes/triangle_mesh.hpp"

#include "../entity/ecs_manager.hpp"
#include "../systems/render_system.hpp"
#include "../systems/physics_system.hpp"
#include "../systems/camera_system.hpp"

// App class that is used to control the program
class App
{
public:
    App(const unsigned width = 1280, const unsigned height = 720, const std::string &title = "OpenGL Project");
    ~App();

    // Run the application
    void run();

private:
    GLFWwindow *window;
    unsigned width, height;
    std::string title;
    unsigned int shader;

    // Initialize GLFW and some OpenGL parameters
    void glfw_init();

    // Load GLAD
    void glad_load();

    // Resizing
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    // Handle mouse
    static void mouse_callback(GLFWwindow* window, double xposin, double yposin);

    // Generate random cubes
    void generate_random_cubes(CubeMesh &cube, const unsigned int n);

    // ECS
    ECSManager ecs;
    RenderSystem render_system;
    PhysicsSystem physics_system;
    CameraSystem camera_system;

    float clock_dt = 0.0f;
    float physics_dt = 0.01f;
    float last_x = 0.0f, last_y = 0.0f;
    bool first_motion = true;

    // Projection specs
    float znear = 0.1f, zfar = 50.f;
    float fov = 90.0f;
    float aspect_ratio;
};