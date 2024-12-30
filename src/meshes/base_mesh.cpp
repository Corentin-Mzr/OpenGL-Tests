#include "base_mesh.hpp"

BaseMesh::~BaseMesh()
{
    glDeleteVertexArrays(1, &vao);

    glDeleteBuffers(1, &vbo_pos);
    // glDeleteBuffers(1, &vbo_color);
    glDeleteBuffers(1, &vbo_uv);
    glDeleteBuffers(1, &vbo_normals);

    // glDeleteBuffers(1, &ebo);
}

// Returns VAO
unsigned int BaseMesh::get_mesh() const
{
    return vao;
}

// Returns vertex count
unsigned int BaseMesh::get_vertex_count() const
{
    return vertex_count;
}

// Set up VAO, VBO, EBO etc.
void BaseMesh::set_up(const std::vector<float> &vertices,
                      const std::vector<float> &uvs,
                      const std::vector<float> &normals)
{
    // Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate VBO for Position and link to layout 0
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Generate VBO for UV Coords and link to layout 1
    if (!uvs.empty())
    {
        glGenBuffers(1, &vbo_uv);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uvs.size(), uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
    }

    // Generate VBO for normals and link to layout 2
    if (!normals.empty())
    {
        glGenBuffers(1, &vbo_normals);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(2);
    }

    // UNBIND VAO
    glBindVertexArray(0);

    // // Vertex Buffer Object for Color Index
    // glGenBuffers(1, &vbo_color);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * color_indices.size(), color_indices.data(), GL_STATIC_DRAW);

    // // Link Color
    // glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(unsigned int), (void *)0);
    // glEnableVertexAttribArray(1);

    // // Vertex Buffer Object for UV Coords Index
    // glGenBuffers(1, &vbo_uv);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * uv_indices.size(), uv_indices.data(), GL_STATIC_DRAW);

    // // Link UV
    // glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(unsigned int), (void *)0);
    // glEnableVertexAttribArray(2);

    // // Element Buffer Object
    // glGenBuffers(1, &ebo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * element_indices.size(), element_indices.data(), GL_STATIC_DRAW);

    
}