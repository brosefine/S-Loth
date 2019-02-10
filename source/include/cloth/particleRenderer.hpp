/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#ifndef PARTICLERENDERER_HPP
#define PARTICLERENDERER_HPP

#include "headers.hpp"
#include <cloth/particleSystem.hpp>

class ParticleRenderer {
public:
	ParticleRenderer() {}
	~ParticleRenderer() {destroy();}

	void generate(ParticleSystem *sys);
	void destroy();
	void update();
	void render();

private:
	ParticleSystem *m_sys = nullptr;
	unsigned int m_buf_pos{0};
	unsigned int m_buf_col{0};
	unsigned int m_buf_indices{0};
	unsigned int m_buf_normals{0};
    unsigned int m_buf_uv{0};
	unsigned int m_vao{0};

};

#endif //PARTICLERENDERER