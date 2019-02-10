#version 420

#define PICK_COLOR 1
#define TEXTURE 2
#define SPRING 4
#define NORMAL 8

layout (location = 0) in vec4 particle_position;
layout (location = 1) in vec4 particle_color;
layout (location = 3) in vec4 particle_normal;
layout (location = 4) in vec4 particle_uv;

uniform mat4 camera_matrix;
uniform mat4 projection_matrix;
uniform mat4 normal_matrix;
uniform vec3 sun_pos;
uniform int color_mode;

out vec4 pass_color;
out vec2 pass_uv;
out vec3 pass_normal;
out vec3 pass_light;
out vec3 pass_cam;
flat out int  pass_color_mode;

void main() {

  vec4 sunPos = camera_matrix * vec4(sun_pos, 1.0);
  vec4 worldPos = camera_matrix * vec4(particle_position.xyz, 1.0);

  pass_normal = normalize((normal_matrix * vec4(particle_normal.xyz, 0.0)).xyz);
  pass_light = normalize(sunPos.xyz - worldPos.xyz);
  pass_cam = normalize(-1 * worldPos.xyz);

  gl_Position = projection_matrix * worldPos;
  pass_uv = vec2(particle_uv.xy);
  pass_color_mode = color_mode;
  pass_color = vec4(particle_color.xyz, 1.0);

  if (bool(color_mode & NORMAL)) {
    pass_color = vec4(particle_normal.xyz,1.0);
  }




}
