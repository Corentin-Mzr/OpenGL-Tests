#version 330 core

layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec2 uv_coords;
layout (location = 2) in vec3 normal;

out vec3 frag_pos;
out vec3 frag_color;
out vec2 frag_texcoord;
out vec3 frag_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertex_pos, 1.0);

    frag_pos = vec3(model * vec4(vertex_pos, 1.0));
    frag_color = vec3(1.0, 1.0, 1.0);
    frag_texcoord = uv_coords;
    frag_normal = mat3(transpose(inverse(model))) * normal;
}


// Input -> transform_component.position + transform_component.euler
// Compute Model Matrix
// Compute View Matrix
// Compute Projection Matrix

// Compute Translation Matrix
mat4 translation_matrix(vec3 pos)
{
    // MAYBE TRANSPOSE
    mat4 trans = mat4(
        1.0, 0.0, 0.0, pos.x,
        0.0, 1.0, 0.0, pos.y,
        0.0, 0.0, 0.0, pos.z,
        0.0, 0.0, 0.0, 1.0
    );

    return trans;
}

// Compute Scale Matrix
mat4 scale_matrix(float s)
{
    mat4 scale = mat4(
        s, 0.0, 0.0, 0.0,
        0.0, s, 0.0, 0.0,
        0.0, 0.0, s, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    return scale;
}

// Compute Rotation Matrix around X axis
// Theta (t) in radians
mat4 rotx_matrix(in float t)
{
    float c = cos(t);
    float s = sin(t);

    mat4 rotx = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, c, -s, 0.0,
        0.0, s, c, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    return rotx;
}

// Compute Rotation Matrix around Y axis
// Theta (t) in radians
mat4 roty_matrix(in float t)
{
    float c = cos(t);
    float s = sin(t);
    mat4 roty = mat4(
        c, 0.0, s, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -s, 0.0, c, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    return roty;
}


// Compute Rotation Matrix around Z axis
// Theta (t) in radians
mat4 rotz_matrix(in float t)
{
    float c = cos(t);
    float s = sin(t);

    mat4 rotz = mat4(
        c, -s, 0.0, 0.0,
        s, c, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    return rotz;
}

// Compute Global Rotation Matrix around all axes
// Angles in radians
mat4 rotation_matrix(in vec3 euler)
{
    return rotz_matrix(euler.z) * roty_matrix(euler.y) * rotx_matrix(euler.x);
}

// Compute the model matrix
mat4 model_matrix(in vec3 position, in vec3 euler, in float scale)
{
    mat4 model = translation_matrix(position) * rotation_matrix(euler) * scale_matrix(scale);
    return model;
}

// Compute the view matrix
mat4 view_matrix(in vec3 eye, in vec3 target, in vec3 up)
{
    vec3 f = normalize(target - eye); // Forward vector
    vec3 r = normalize(cross(f, up)); // Right vector
    vec3 u = cross(r, f); // Corrected up vector

    mat4 view = mat4(
        vec4(r, -dot(r, eye)),
        vec4(u, -dot(u, eye)),
        vec4(-f, dot(f, eye)),
        vec4(0.0, 0.0, 0.0, 1.0)
    );

    return view;
}

// Compute the projection matrix
mat4 proj_matrix(in float fov, in float aspect_ratio, in float znear, in float zfar)
{
    float tan_hfov = tan(radians(fov) / 2.0);
    mat4 projection = mat4(
        1.0 / (aspect_ratio * tan_hfov), 0.0, 0.0, 0.0,
        0.0, 1.0 / tan_hfov, 0.0, 0.0,
        0.0, 0.0, -(zfar + znear) / (zfar - znear), -(2.0 * zfar * znear) / (zfar - znear),
        0.0, 0.0, -1.0, 0.0
    );

    return projection;
}