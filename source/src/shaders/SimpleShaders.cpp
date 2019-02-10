#include <shaders/SimpleShaders.h>
#include <iostream>
#include <fstream>

void SimpleShaders::destroy() {
    glUseProgram(0);
    glDeleteProgram(m_shader_program);
}
// load vertex and fragment shaders, create and activate shader program, check for errors
bool SimpleShaders::loadVertexFragmentShaders(const char* vertexShaderFilename, const char* fragmentShaderFilename){
	// Create empty shader object (vertex shader)
	m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	// Read vertex shader source 
	std::string shaderSource = readFile( vertexShaderFilename );
	const char* sourcePtr = shaderSource.c_str();

	// Attach shader code
	glShaderSource(m_vertex_shader, 1, &sourcePtr, NULL);

	// Compile
	glCompileShader(m_vertex_shader);
	printShaderInfoLog(m_vertex_shader);

	// Create empty shader object (fragment shader)
	m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader source 
	shaderSource = readFile( fragmentShaderFilename );
	sourcePtr = shaderSource.c_str();

	// Attach shader code
	glShaderSource(m_fragment_shader, 1, &sourcePtr, NULL);

	// Compile
	glCompileShader(m_fragment_shader);
	printShaderInfoLog(m_fragment_shader);

	// Create shader program
	m_shader_program = glCreateProgram();

	// Attach shader
	glAttachShader(m_shader_program, m_vertex_shader);
	glAttachShader(m_shader_program, m_fragment_shader);

	// Link program
	glLinkProgram(m_shader_program);
	glDeleteShader(m_vertex_shader);
	glDeleteShader(m_fragment_shader);
	printProgramInfoLog();


	std::cout << "Vertex/Fragment Shaders loaded\n" << std::endl;
	return true;
}

void SimpleShaders::activate(){
	glPolygonMode(GL_FRONT_AND_BACK, mDrawMode);
	glUseProgram(m_shader_program);
}

void SimpleShaders::deactivate(){
	glUseProgram(0);
}

// Reads a file and returns the content as a string
std::string SimpleShaders::readFile(std::string fileName){
	std::string fileContent;
	std::string line;

	std::ifstream file(fileName.c_str());
	if (file.is_open()) {
		while (!file.eof()){
			getline (file,line);
			line += "\n";
			fileContent += line;					
		}
		file.close();
	}
	else
		std::cout << "ERROR: Unable to open file " << fileName << std::endl;

	return fileContent;
}

// Print information about the compiling step
void SimpleShaders::printShaderInfoLog(GLuint shader){
    GLint infologLength = 0;
    GLsizei charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}

// Print information about the linking step
void SimpleShaders::printProgramInfoLog(){
	GLint infoLogLength = 0;
	GLsizei charsWritten  = 0;
	char *infoLog;

	glGetProgramiv(m_shader_program, GL_INFO_LOG_LENGTH,&infoLogLength);
	if (infoLogLength > 0)
	{
		infoLog = (char *)malloc(infoLogLength);
		glGetProgramInfoLog(m_shader_program, infoLogLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}

GLuint SimpleShaders::getUniform(std::string uniform) const{
	auto search = m_uniforms.find(uniform);
	if(search != m_uniforms.end()){
		return search->second;
	} else {
		std::cout << "ERROR: uniform " << uniform << " not found!" << std::endl;
		return 0;
	}
}

void SimpleShaders::addUniform(const char* uniform){

	activate();
	GLuint uniform_location = glGetUniformLocation(m_shader_program, uniform);
	deactivate();
	m_uniforms.insert(std::make_pair(std::string(uniform), uniform_location));

}

