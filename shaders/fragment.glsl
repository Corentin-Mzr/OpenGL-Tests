#version 330 core

in vec3 frag_pos;
in vec3 frag_color;
in vec2 frag_texcoord;
in vec3 frag_normal;

out vec4 screen_color;

uniform sampler2D material;

uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main()
{
    // Ambient Lighting
    float ambient_strenght = 0.1;
    vec3 ambient = ambient_strenght * light_color;

    // Diffuse Lighting
    vec3 norm = normalize(frag_normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    // Specular Lighting
    float specular_strengh = 0.5;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strengh * spec * light_color;

    // Output Lighting
    vec3 result = (ambient + diffuse + specular) * frag_color;

    // Texture
    vec4 tex_color = texture(material, frag_texcoord);

    // When no texture just put the color
    if (tex_color.rgb == vec3(0.0))
        screen_color = vec4(result, 1.0);
    else
        screen_color = tex_color * vec4(result, 1.0);
}