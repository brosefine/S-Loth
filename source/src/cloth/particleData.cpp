/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#include <cloth/particleData.hpp>

////////////////////////////////////////////////////////////////////////////////

void ParticleData::generate(size_t maxSize){
	m_count = maxSize;
	m_count_alive = 0;
	m_pos.reset(new glm::vec4[maxSize]);
	m_pos_prev.reset(new glm::vec4[maxSize]);
	m_col.reset(new glm::vec4[maxSize]);
	m_acc.reset(new glm::vec4[maxSize]);
    m_mass.reset(new float[maxSize]);
	m_alive.reset(new bool[maxSize]);
	m_normal.reset(new glm::vec4[maxSize]);
	m_uv.reset(new glm::vec4[maxSize]);

    m_indices = std::make_shared<std::vector<unsigned int>>();
    m_struct_con = std::make_shared<std::vector<glm::vec3>>();
    m_shear_con = std::make_shared<std::vector<glm::vec3>>();
    m_bend_con = std::make_shared<std::vector<glm::vec3>>();
}


void ParticleData::wake(size_t id){
	//only called on particles behind last alive particles, no swap necessary
	m_alive[id] = true;
	m_pos[id] = glm::vec4(0.0f);
	m_pos_prev[id] = glm::vec4(0.0f);
	m_col[id] = glm::vec4(0.0f);
	m_acc[id] = glm::vec4(0.0f);
    m_mass[id] = 1.f;
	m_normal[id] = glm::vec4(0.0f);
	m_uv[id] = glm::vec4(0.0f);
	m_count_alive ++;
}
////////////////////////////////////////////////////////////////////////////////
