#include "render_system.hpp"

RenderSystem::RenderSystem(const unsigned int shader, GLFWwindow* window) : window(window)
{
    model_loc = glGetUniformLocation(shader, "model");
}

// Update entities that have a RenderComponent and a TransformComponent
void RenderSystem::update(ECSManager &ecs)
{
    auto &transform_components = ecs.get_transforms();
    auto &render_components = ecs.get_renders();

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw entities
    for (const auto& [entity, mask]: ecs.get_masks())
    {
        // Check for RenderComponent and TransformComponent
        if ((mask & static_cast<unsigned int>(ComponentType::TRANSFORM)) &&
        mask & static_cast<unsigned int>(ComponentType::RENDER))
        {
            const TransformComponent &transform = transform_components[entity];
            const RenderComponent &render = render_components[entity];

            // Model matrix
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform.position);
            model = glm::rotate(model, glm::radians(transform.euler.x), {1.0f, 0.0f, 0.0f});
            model = glm::rotate(model, glm::radians(transform.euler.y), {0.0f, 1.0f, 0.0f});
            model = glm::rotate(model, glm::radians(transform.euler.z), {0.0f, 0.0f, 1.0f});
            glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

            // Bind mesh and texture
            glBindTexture(GL_TEXTURE_2D, render.material);

            glBindVertexArray(render.mesh);
            glDrawArrays(GL_TRIANGLES, 0, render.vertex_count);
            // glDrawElements(GL_TRIANGLES, render.vertex_count, GL_UNSIGNED_INT, 0);
        }
    }

    // Display
    glfwSwapBuffers(window);
}