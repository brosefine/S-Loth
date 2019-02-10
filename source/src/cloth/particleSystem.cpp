/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#include <cloth/particleSystem.hpp>

ParticleSystem::ParticleSystem(size_t maxCount, std::shared_ptr<Camera> cam)
	: m_camera{cam} {
	m_count = maxCount;
	m_particles.generate(maxCount);
	for (size_t i = 0; i < maxCount; ++i){
		m_particles.m_alive[i] = false;
	}
	
}

void ParticleSystem::update(float dt){
	if(do_update) {

		if(getAliveCount() > 0){
			for (size_t i = 0; i < m_count; ++i){
				m_particles.m_acc[i] = glm::vec4(0.0f);
			}

			for(auto& up : m_updaters) {
				up->update(dt, &m_particles);
			}

          if(do_emit) {
            for (auto& em: m_emitters){
              em->emit(0, &m_particles);
            }
          }
		}
	}
	
}

void ParticleSystem::emit(){
	if(do_emit) {
		for (auto& em: m_emitters){
			em->emit(0, &m_particles);
		}
	}
}

void ParticleSystem::reset(){
	m_particles.m_count_alive = 0;
}
