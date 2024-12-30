#pragma once

struct RenderComponent
{
    unsigned int mesh, vertex_count, material;
    RenderComponent(const unsigned int mesh = 0,
                    const unsigned int vcount = 0,
                    const unsigned int mat = 0) : mesh(mesh), vertex_count(vcount), material(mat)
    {
    }

    // Friend declaration for the << operator
    friend std::ostream &operator<<(std::ostream &os, const RenderComponent &rc)
    {
        os << "RenderComponent(mesh=" << rc.mesh
           << ", vertex_count=" << rc.vertex_count
           << ", material=" << rc.material << ")";
        return os;
    }
};