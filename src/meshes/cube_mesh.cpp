#include "cube_mesh.hpp"

CubeMesh::CubeMesh()
{
    std::vector<float> vertices{
        // Front Face
        -0.5f, -0.5f, 0.5f, // Front Bottom Left
        -0.5f, 0.5f, 0.5f,  // Front Top Left
        0.5f, 0.5f, 0.5f,   // Front Top Right

        -0.5f, -0.5f, 0.5f, // Front Bottom Left
        0.5f, 0.5f, 0.5f,   // Front Top Right
        0.5f, -0.5f, 0.5f,  // Front Bottom Right

        // Back Face
        -0.5f, -0.5f, -0.5f, // Back Bottom Left
        -0.5f, 0.5f, -0.5f,  // Back Top Left
        0.5f, 0.5f, -0.5f,   // Back Top Right

        -0.5f, -0.5f, -0.5f, // Back Bottom Left
        0.5f, 0.5f, -0.5f,   // Back Top Right
        0.5f, -0.5f, -0.5f,  // Back Bottom Right

        // Right Face
        0.5f, -0.5f, 0.5f,  // Front Bottom Right
        0.5f, 0.5f, 0.5f,   // Front Top Right
        0.5f, 0.5f, -0.5f,   // Back Top Right

        0.5f, -0.5f, 0.5f,  // Front Bottom Right
        0.5f, 0.5f, -0.5f,   // Back Top Right
        0.5f, -0.5f, -0.5f,  // Back Bottom Right

        // Left Face
        -0.5f, -0.5f, -0.5f, // Back Bottom Left
        -0.5f, 0.5f, -0.5f,  // Back Top Left
        -0.5f, 0.5f, 0.5f,  // Front Top Left

        -0.5f, -0.5f, -0.5f, // Back Bottom Left
        -0.5f, 0.5f, 0.5f,  // Front Top Left
        -0.5f, -0.5f, 0.5f, // Front Bottom Left

        // Top Face
        -0.5f, 0.5f, 0.5f,  // Front Top Left
        -0.5f, 0.5f, -0.5f,  // Back Top Left
        0.5f, 0.5f, -0.5f,   // Back Top Right

        -0.5f, 0.5f, 0.5f,  // Front Top Left
        0.5f, 0.5f, -0.5f,   // Back Top Right
        0.5f, 0.5f, 0.5f,   // Front Top Right

        // Bottom Face
        -0.5f, -0.5f, -0.5f, // Back Bottom Left
        -0.5f, -0.5f, 0.5f, // Front Bottom Left
        0.5f, -0.5f, 0.5f,  // Front Bottom Right

        -0.5f, -0.5f, -0.5f, // Back Bottom Left
        0.5f, -0.5f, 0.5f,  // Front Bottom Right
        0.5f, -0.5f, -0.5f,  // Back Bottom Right

    };

    std::vector<float> uvs{
        // Front Face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Back Face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Right Face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Left Face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Top Face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Bottom Face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

    };

    std::vector<float> normals{
        // Front Face
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        // Back Face
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        // Right Face
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        // Left Face
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        // Top Face
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        // Bottom Face
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
    };

    vertex_count = 36;

    set_up(vertices, uvs, normals);
}