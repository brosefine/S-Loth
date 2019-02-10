/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include <cloth/particleData.hpp>
#include <cloth/particleGenerators.hpp>

class ParticleEmitter {
public:
	float m_emit_rate{0.0};

	ParticleEmitter() { }
	ParticleEmitter(float emit) : m_emit_rate{emit} { }
	virtual ~ParticleEmitter() { }

	// calls all the generators and at the end it activates (wakes) particle
	virtual void emit(float dt, ParticleData *p);
	void addGenerator(std::shared_ptr<ParticleGenerator> gen) { m_generators.push_back(gen); }

protected:
	std::vector<std::shared_ptr<ParticleGenerator>> m_generators;
};

#endif //PARTICLEEMITTER