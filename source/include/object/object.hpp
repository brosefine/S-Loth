#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <cloth/headers.hpp>


class Object {

public:

	Object(){}
	~Object(){destroy();}

	float* get_model_matrix();

	void translate(glm::fvec3 const& v);
	void rotate(glm::fvec3 const& axis, float r);
	void scale(float scale);

    void set_translate(glm::fvec3 const& v);
    void set_rotate(glm::fvec3 const& axis, float r);
    void set_scale(float scale);

	void activate() const;
	void deactivate() const;
	void draw() const;

	virtual void load();

protected:
	virtual void init() = 0;
	virtual void destroy();
	//data
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	//buffers
	GLuint m_vao = 0;
	GLuint m_buf_pos = 0;
	GLuint m_buf_indices = 0;
	// primitive type to draw
	GLenum m_draw_mode = GL_NONE;

	glm::fmat4 m_translation_matrix = glm::fmat4{1.0};
	glm::fmat4 m_rotation_matrix = glm::fmat4{1.0};
	glm::fmat4 m_scale_matrix = glm::fmat4{1.0};
	glm::fmat4 m_model_matrix = glm::fmat4{1.0};

};

class Cube : public Object {
protected:
	void init() override;
};

class Sphere : public Object {
protected:
    void init() override;
};


#endif