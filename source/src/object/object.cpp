#include <object/object.hpp>

float* Object::get_model_matrix(){
  m_model_matrix = m_translation_matrix * m_scale_matrix* m_rotation_matrix;
  return glm::value_ptr(m_model_matrix);
}

void Object::translate(glm::fvec3 const& v){
  m_translation_matrix = glm::translate(m_translation_matrix, v);
}

void Object::set_translate(glm::fvec3 const &v) {
  m_translation_matrix = glm::translate(glm::fmat4{}, v);
}

void Object::rotate(glm::fvec3 const& axis, float r){
  m_rotation_matrix = glm::rotate(m_rotation_matrix, r, axis);
}

void Object::set_rotate(glm::fvec3 const &axis, float r) {
  m_rotation_matrix = glm::rotate(glm::fmat4{}, r, axis);

}

void Object::scale(float scale){
  m_scale_matrix = glm::scale(m_scale_matrix, glm::fvec3{scale, scale, scale});
}

void Object::set_scale(float scale) {
  m_scale_matrix = glm::scale(glm::fmat4{}, glm::fvec3{scale, scale, scale});
}

void Object::activate() const {
  glBindVertexArray(m_vao);
}

void Object::deactivate() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Object::draw() const {
  activate();
  if(m_indices.size() != 0) {
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(m_vao);
  } else {
    glBindVertexArray(m_vao);
    glDrawArrays(GL_LINE_STRIP, 0, m_vertices.size() / 3);
    glBindVertexArray(0);
  }
  deactivate();
}

void Object::destroy() {
  if(m_buf_pos != 0){
    glDeleteBuffers(1, &m_buf_pos);
    m_buf_pos = 0;
  }

  if(m_buf_indices != 0){
    glDeleteBuffers(1, &m_buf_indices);
    m_buf_indices = 0;
  }

  if(m_vao != 0){
    glDeleteBuffers(1, &m_vao);
    m_vao = 0;
  }
}

void Object::load() {
  init();

  // generate vertex array object
  glGenVertexArrays(1, &m_vao);
  // bind the array for attaching buffers
  glBindVertexArray(m_vao);

  // generate generic buffer
  glGenBuffers(1, &m_buf_pos);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, m_buf_pos);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
  // activate second attribute on gpu

  if(m_indices.size() != 0){
    glGenBuffers(1, &m_buf_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buf_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Cube::init(){
  //cube's vertices
  m_vertices.push_back(-0.5f); m_vertices.push_back(-0.5f); m_vertices.push_back(0.5f);
  m_vertices.push_back(0.5f); m_vertices.push_back(-0.5f); m_vertices.push_back(0.5f);
  m_vertices.push_back(-0.5f); m_vertices.push_back(0.5f); m_vertices.push_back(0.5f);
  m_vertices.push_back(0.5f); m_vertices.push_back(0.5f); m_vertices.push_back(0.5f);
  m_vertices.push_back(-0.5f); m_vertices.push_back(0.5f); m_vertices.push_back(-0.5f);
  m_vertices.push_back(0.5f); m_vertices.push_back(0.5f); m_vertices.push_back(-0.5f);
  m_vertices.push_back(-0.5f); m_vertices.push_back(-0.5f); m_vertices.push_back(-0.5f);
  m_vertices.push_back(0.5f); m_vertices.push_back(-0.5f); m_vertices.push_back(-0.5f);

  //cube's faces
  m_indices.push_back(0); m_indices.push_back(1); m_indices.push_back(2);
  m_indices.push_back(2); m_indices.push_back(1); m_indices.push_back(3);
  m_indices.push_back(2); m_indices.push_back(3); m_indices.push_back(4);
  m_indices.push_back(4); m_indices.push_back(3); m_indices.push_back(5);
  m_indices.push_back(4); m_indices.push_back(5); m_indices.push_back(6);
  m_indices.push_back(6); m_indices.push_back(5); m_indices.push_back(7);
  m_indices.push_back(6); m_indices.push_back(7); m_indices.push_back(2);
  m_indices.push_back(0); m_indices.push_back(7); m_indices.push_back(1);
  m_indices.push_back(1); m_indices.push_back(7); m_indices.push_back(3);
  m_indices.push_back(3); m_indices.push_back(7); m_indices.push_back(5);
  m_indices.push_back(6); m_indices.push_back(0); m_indices.push_back(4);
  m_indices.push_back(4); m_indices.push_back(0); m_indices.push_back(2);

}

void Sphere::init(){
  glm::vec4 point;
  int rings = 20, edges = 40;
  float step_y = M_PI / (rings),
        step_x = 2.f * M_PI / edges,
        offset = 4.f * M_PI / rings,
        angle;
  //rings of sphere
  for(int j = 0; j <= rings; ++j) {
    angle = M_PI / 2.f + step_y * j;
    //points in each ring
    for (int i = 0; i <= edges; ++i) {
      point = glm::rotate(glm::fmat4{}, step_x * i + offset * j, glm::vec3(0.f, 1.f, 0.f))
              * glm::vec4(cos(angle), sin(angle), 0.f, 1.f);
      m_vertices.push_back(point.x);
      m_vertices.push_back(point.y);
      m_vertices.push_back(point.z);

    }
  }
}

