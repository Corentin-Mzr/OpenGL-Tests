#include "app.hpp"

App::App(const unsigned width, const unsigned height, const std::string &title) : width(width), height(height), title(title), physics_dt(0.01f)
{
    // Init GLFW
    glfw_init();

    // Create the window and make it current context
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create a GLFW window");
    }
    std::cout << "Create Window OK\n";

    // Make the window the current context
    glfwMakeContextCurrent(window);

    // Disable VSync
    glfwSwapInterval(0);

    // Load GLAD
    glad_load();

    // Set viewport, callback function when resizing and background color
    glViewport(0, 0, width, height);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glClearColor(0.25f, 0.5f, 0.3f, 1.0f);
    std::cout << "View Port, Framebuffer, Clear color OK\n";

    // Create a shader
    shader = make_shader_program(
        "../shaders/vertex.glsl",
        "../shaders/fragment.glsl");
    std::cout << "Shader Program OK\n";

    // Set-up render system
    render_system = RenderSystem(shader, window);
    std::cout << "Render System OK\n";

    // Set-up camera system
    camera_system = CameraSystem(shader, window);
    std::cout << "Camera System OK\n";

    // Compute aspect ratio
    aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
}

App::~App()
{
    // Clean delete
    glDeleteProgram(shader);
    glfwTerminate();
}

// Initialize GLFW and some OpenGL parameters
void App::glfw_init()
{
    if (!glfwInit())
        throw std::runtime_error("GLFW could not be initialized");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << "GLFW Init OK\n";
}

// Load GLAD
void App::glad_load()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Could not load GLAD");
    }
    std::cout << "GLAD Load OK\n";
}

// Resizing
void App::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
    app->aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
}

// Handle mouse
void App::mouse_callback(GLFWwindow *window, double xposin, double yposin)
{
    auto app = static_cast<App *>(glfwGetWindowUserPointer(window));

    const float xpos = static_cast<float>(xposin);
    const float ypos = static_cast<float>(yposin);

    if (app->first_motion)
    {
        app->last_x = xpos;
        app->last_y = ypos;
        app->first_motion = false;
    }

    const float xoffset = xpos - app->last_x;
    const float yoffset = app->last_y - ypos;

    app->last_x = xpos;
    app->last_y = ypos;
    app->camera_system.set_offset(xoffset, yoffset);
}

// Run the application
void App::run()
{
    SquareMesh square;
    Material wall("../textures/wall.jpg");
    Material mask("../textures/mask.jpg");
    TriangleMesh triangle;
    CubeMesh cube;

    // Create square entity
    // unsigned int square_entity = ecs.create_entity();
    RenderComponent render_component{square.get_mesh(), square.get_vertex_count(), wall.get_material()};
    TransformComponent transform_component{glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}};
    PhysicsComponent physics_component{glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}};
    // ecs.add_component(square_entity, render_component);
    // ecs.add_component(square_entity, transform_component);
    // ecs.add_component(square_entity, physics_component);

    // Create cube entity
    unsigned int cube_entity = ecs.create_entity();
    render_component.mesh = cube.get_mesh();
    render_component.material = wall.get_material();
    render_component.vertex_count = cube.get_vertex_count();
    transform_component.position = glm::vec3{2.0f, 0.0f, 2.0f};
    physics_component.euler_velocity = glm::vec3{0.0f, 0.0f, 0.0f};
    ecs.add_component(cube_entity, render_component);
    ecs.add_component(cube_entity, transform_component);
    ecs.add_component(cube_entity, physics_component);

    // unsigned int triangle_entity = ecs.create_entity();
    // RenderComponent render_component{triangle.get_mesh(), triangle.get_vertex_count(), wall.get_material()};
    // TransformComponent transform_component{glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}};
    // ecs.add_component(triangle_entity, render_component);
    // ecs.add_component(triangle_entity, transform_component);


    generate_random_cubes(cube, 4000);

    // Create camera
    unsigned int camera = ecs.create_entity();
    CameraComponent camera_component;
    TransformComponent camera_position{glm::vec3{0.0f, 0.0f, 0.5f}, glm::vec3{0.0, 0.0, 0.0}};
    ecs.add_component(camera, camera_position);
    ecs.add_component(camera, camera_component);

    // Projection matrix
    unsigned int proj_loc = glGetUniformLocation(shader, "projection");
    glm::mat4 proj = glm::perspective(glm::radians(fov), aspect_ratio, znear, zfar);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

    // Lighting
    unsigned int light_color_loc = glGetUniformLocation(shader, "light_color");
    glm::vec3 light_color{1.0f, 0.5f, 0.0f};
    glUniform3fv(light_color_loc, 1, glm::value_ptr(light_color));

    unsigned int light_pos_loc = glGetUniformLocation(shader, "light_pos");
    glm::vec3 light_pos{0.0f, 5.0f, 0.0f};
    glUniform3fv(light_pos_loc, 1, glm::value_ptr(light_pos));

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);

    // Variables to track time
    float previous_time = static_cast<float>(glfwGetTime());
    float current_time;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Handle events and inputs
        glfwPollEvents();

        // Compute delta time
        current_time = static_cast<float>(glfwGetTime());
        clock_dt = current_time - previous_time;
        previous_time = current_time;
        camera_system.update(ecs, clock_dt);

        // Update physics
        physics_system.update(ecs, physics_dt);

        // Draw
        render_system.update(ecs);
    }
}

// Generate random cubes
void App::generate_random_cubes(CubeMesh &cube, const unsigned int n)
{
    // Create a cube mesh and define necessary components
    TransformComponent transform_component;
    PhysicsComponent physics_component;
    RenderComponent render_component;
    unsigned int cube_entity;

    // Set the Seed
    std::srand(std::time(0));

    for (int i = 0; i < n; ++i)
    {
        float x = std::rand() % 50 - 25;
        float y = std::rand() % 50 - 25;
        float z = std::rand() % 50 - 25;

        float vx = std::rand() % 10 - 5;
        float vy = std::rand() % 10 - 5;
        float vz = std::rand() % 10 - 5;

        unsigned int cube_entity = ecs.create_entity();
        render_component.mesh = cube.get_mesh();
        render_component.material = 0;
        render_component.vertex_count = cube.get_vertex_count();
        transform_component.position = glm::vec3{x, y, z};
        physics_component.euler_velocity = glm::vec3{vx, vy, vz};
        ecs.add_component(cube_entity, render_component);
        ecs.add_component(cube_entity, transform_component);
        ecs.add_component(cube_entity, physics_component);
    }
}