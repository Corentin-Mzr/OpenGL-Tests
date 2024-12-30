#include "square_mesh.hpp"

SquareMesh::SquareMesh()
{
    // Position in NDC coords and color
    std::vector<float> vertices{
        // First triangle
        -0.5f, -0.5f, 0.0f, // Bottom Left
        -0.5f, 0.5f, 0.0f,  // Top Left
        0.5f, 0.5f, 0.0f,   // Top Right

        // Second Triangle
        -0.5f, -0.5f, 0.0f, // Bottom Left
        0.5f, 0.5f, 0.0f,   // Top Right
        0.5f, -0.5f, 0.0f,  // Bottom Right
    };

    // std::vector<unsigned int> color_indices{
    //     0, 1, 2, 3
    // };

    // std::vector<unsigned int> element_indices{
    //     0, 1, 2, 
    //     0, 2, 3
    // };

    // std::vector<unsigned int> uv_indices{
    //     0, 1, 2, 3
    // };

    std::vector<float> uvs{
        // First triangle
        0.0f, 0.0f, // Bottom Left
        1.0f, 0.0f, // Top Left
        1.0f, 1.0f, // Top Right

        // Second Triangle
        0.0f, 0.0f, // Bottom Left
        1.0f, 1.0f, // Top Right
        0.0f, 1.0f, // Bottom Right
    };

    std::vector<float> normals{
        // First triangle
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,

        // Second triangle
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
    };
    vertex_count = 6;

    set_up(vertices, uvs, normals);
}