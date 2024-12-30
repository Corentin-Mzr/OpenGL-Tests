#pragma once

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Simple class to handle a texture
class Material
{
public:
    Material(const std::string &filepath);
    ~Material();

    // Use the texture
    void use(const unsigned int unit);

    // Returns texture
    unsigned int get_material() const;

private:
    unsigned int texture;
};