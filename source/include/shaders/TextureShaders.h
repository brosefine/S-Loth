#ifndef TEXTURE_SHADERS_H
#define TEXTURE_SHADERS_H

#include <SOIL/SOIL.h>
#include <shaders/SimpleShaders.h>


class TextureShaders : public SimpleShaders
{
public:
	virtual ~TextureShaders(){destroy();};

	void activate() override;
    void deactivate() override;

	void addTexture(int imageX, int imageY, const char* location);


private:
    void destroy() override;

	std::vector<GLuint> m_textures;

};

#endif
