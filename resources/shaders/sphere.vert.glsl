#version 420
layout (location = 0) in vec3 vertex_position;

uniform mat4 camera_matrix;
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform vec4 in_color;


out vec4 pass_color;

void main() {
    gl_Position = (projection_matrix * camera_matrix * model_matrix) * vec4(vertex_position, 1.0);
    pass_color = vec4(in_color.xyz, 1.0);
}
