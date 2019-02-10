#ifndef SIMPLE_SHADERS_H
#define SIMPLE_SHADERS_H

#include <cloth/headers.hpp>

class SimpleShaders{
public:
	SimpleShaders(){}
	~SimpleShaders(){destroy();}

	bool loadVertexFragmentShaders(const char* vertexShaderFilename, const char* fragmentShaderFilename);

	virtual void activate();
	virtual void deactivate();

	GLuint getUniform(std::string uniform) const;
	void addUniform(const char* uniform);

	GLuint mDrawMode = GL_FILL;


protected:
	std::string readFile(std::string fileName);

	void printShaderInfoLog(GLuint shader);
	void printProgramInfoLog();
	virtual void destroy();

	GLuint m_vertex_shader;
	GLuint m_fragment_shader;
	GLuint m_shader_program;
	std::map<std::string, GLuint> m_uniforms;
};

#endif
