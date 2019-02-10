#version 420

#define PICK_COLOR 1
#define TEXTURE 2
#define SPRING 4
#define NORMAL 8

layout (location = 0) out vec4 fragment_color;

vec3 diffuse_light = vec3(0.8,0.8,0.8);
vec3 specular_light = vec3(0.8,0.8,0.8);
vec3 ambient_light = vec3(0.8,0.8,0.8);
float shiny = 7.0;

in vec4 pass_color;
in vec2 pass_uv;
in vec3 pass_normal;
in vec3 pass_light;
in vec3 pass_cam;
flat in int  pass_color_mode;


uniform vec3 amb;
uniform vec3 diff;
uniform vec3 spec;
uniform sampler2D texture1;


vec3 ambientLighting(vec3 col){

	return col * ambient_light;
}

//calculate diffuse color part (rgb)
vec3 diffuseLighting(in vec3 N, in vec3 L, vec3 col){


	float diffuseTerm = clamp(dot(N,L),0,1);
	return col * diffuse_light * diffuseTerm;

}

//calculate specular color part (rgb)
vec3 specularLighting(in vec3 N, in vec3 L, in vec3 V){

	float specularTerm = 0;

	if(dot(N, L) > 0){
		vec3 H = normalize(L+V);
		specularTerm = pow(dot(N,H), shiny);
	}

	return spec * specular_light * specularTerm;
}

void main() {

  vec3 L = normalize(pass_light);
  vec3 V = normalize(pass_cam);
  vec3 N = normalize(pass_normal);
  vec3 tex_color = texture(texture1, pass_uv).xyz;

  if(dot(N, V) < 0) { N = -N;}

  vec3 out_amb, out_dif;
  if (bool(pass_color_mode & TEXTURE)) {
    out_amb = ambientLighting(tex_color);
    out_dif = diffuseLighting(N, L, tex_color);
  } else {
    out_amb = ambientLighting(amb);
    out_dif = diffuseLighting(N, L, diff);
  }

  vec3 out_spe = specularLighting(N, L, V);


  fragment_color = vec4((out_amb + out_dif + out_spe), 1.0);

  if (bool(pass_color_mode & SPRING) || bool(pass_color_mode & NORMAL)) {
    fragment_color = pass_color;
  }
}