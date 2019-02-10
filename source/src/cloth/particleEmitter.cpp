/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#include <cloth/particleEmitter.hpp>

void ParticleEmitter::emit(float dt, ParticleData *p){
	const size_t new_particles = static_cast<size_t>(m_emit_rate);
	const size_t start_id = p->m_count_alive;
	const size_t end_id = std::min(start_id + new_particles, p->m_count-1);

	for (size_t i = start_id; i <= end_id; ++i)
		p->wake(i);
	
	for (auto &gen : m_generators)
		gen->generate(dt, p, start_id, end_id);

}
