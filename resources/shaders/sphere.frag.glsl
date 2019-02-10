#version 420
in vec4 pass_color;
layout (location = 0) out vec4 fragment_color;


void main() {
    fragment_color = pass_color;
}
