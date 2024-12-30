#include "triangle_mesh.hpp"

TriangleMesh::TriangleMesh()
{
    std::vector<float> vertices{
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    std::vector<float> uvs{
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };

    std::vector<float> normals{
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };
    vertex_count = 3;

    set_up(vertices, uvs, normals);
}
