#pragma once

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class BaseMesh
{
public:
    ~BaseMesh();

    // Returns VAO
    unsigned int get_mesh() const;

    // Returns vertex count
    unsigned int get_vertex_count() const;

protected:
    unsigned int vao, vbo_pos, vbo_uv, vbo_normals, vertex_count;

    // Set up VAO, VBO, EBO etc.
    void set_up(const std::vector<float> &vertices,
                const std::vector<float> &uvs,
                const std::vector<float> &normals);
};