#include <shaders/TextureShaders.h>

#include <glm/gtc/matrix_transform.hpp>

void TextureShaders::destroy() {
  for(auto& tex : m_textures){
    glDeleteTextures(1, &tex);
  }
}

void TextureShaders::activate(){
  SimpleShaders::activate(); // calls activate of inheritated class

  //activate all stored textures
  if(m_textures.size() != 0) {
    int i = 1;
    for(auto const& tex : m_textures){
      glActiveTexture(GL_TEXTURE0 + (i++));
      glBindTexture(GL_TEXTURE_2D, tex);
    }
  }

}

void TextureShaders::deactivate() {
  glActiveTexture(GL_TEXTURE0);
  SimpleShaders::deactivate();
}


// for adding multiple textures
void TextureShaders::addTexture(int imageX, int imageY, const char* location){
  activate();
  GLuint texture_location = -1;
  unsigned char* texture_data = SOIL_load_image(location,&imageX, &imageY, 0, SOIL_LOAD_RGB);
  glGenTextures(1, &texture_location);
  glBindTexture(GL_TEXTURE_2D, texture_location);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageX, imageY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
  glGenerateMipmap(GL_TEXTURE_2D);

  m_textures.push_back(texture_location);

  glBindTexture(GL_TEXTURE_2D, 0);
  deactivate();

}