/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#include <cloth/particleGenerators.hpp>

/******************************************************************************
void generate(float dt, ParticleData *p, size_t start_id, size_t end_id){
	for (size_t i = start_id; i <= end_id; ++i) {
		//do stuff
	}
}
******************************************************************************/


void GridPosGen::generate(float dt, ParticleData *p, size_t start_id, size_t end_id) {
	glm::fvec4 new_pos;
	new_pos.w = 1;

    auto pos = p->m_pos.get();
    auto ind = p->m_indices;
	for(unsigned int i = start_id; i <= end_id; ++i){
		if(i / m_h > m_w) break;
		new_pos.x = (i % m_w) * m_d - (m_w / 2) * m_d;
        new_pos.y = 0;
        new_pos.z = (i / m_w) * m_d - (m_h / 2) * m_d;

		new_pos = m_rot * new_pos;

		pos[i].x = new_pos.x ;
		pos[i].y = new_pos.y;
		pos[i].z = new_pos.z ;
	}
}

void PrevPosGen::generate(float dt, ParticleData *p, size_t start_id, size_t end_id) {
  for (size_t i = start_id; i <= end_id; ++i) {
    p->m_pos_prev[i] = p->m_pos[i];
  }
}

void SpringGen::generate(float dt, ParticleData *p, size_t start_id, size_t end_id) {
	glm::fvec4* pos = p->m_pos.get();
	auto struc = p->m_struct_con;
	for(auto& s : *struc){
		s.z = glm::length(glm::vec3(pos[(int)s.x] - pos[(int)s.y]));
	}

	auto shear = p->m_shear_con;
	for(auto& s : *shear){
		s.z = glm::length(glm::vec3(pos[(int)s.x] - pos[(int)s.y]));
	}

	auto bend = p->m_bend_con;
	for(auto& s : *bend){
		s.z = glm::length(glm::vec3(pos[(int)s.x] - pos[(int)s.y]));
	}
}

void MeshMassGen::generate(float dt, ParticleData *p, size_t start_id, size_t end_id){
	auto mass = p->m_mass.get();
	auto tris = p->m_indices.get();
	float tri_mass = m_total_mass / tris->size();

	for (size_t i = start_id; i <= end_id; ++i) {
		mass[i] = 0;
	}

	for(int i : *tris){
		mass[i] += tri_mass;
	}
}
