#include "material.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Material::Material(const std::string &filepath)
{
    // Generate texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    // Send data to the GPU
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "[MATERIAL CREATION ERROR]\n"
                  << "Could not load texture\n";
    }

    // Free texture
    stbi_image_free(data);
}

Material::~Material()
{
    glDeleteTextures(1, &texture);
}

// Use the texture
void Material::use(const unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

// Returns texture
unsigned int Material::get_material() const
{
    return texture;
}