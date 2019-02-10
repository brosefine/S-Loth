/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "headers.hpp"
#include <camera/Camera.h>
#include <cloth/particleUpdaters.hpp>
#include <cloth/particleEmitter.hpp>

class ParticleSystem {
public:
	ParticleSystem(size_t maxCount, std::shared_ptr<Camera> cam);
	virtual ~ParticleSystem() { }
	//ParticleSystem(const ParticleSystem &) = delete;
	//ParticleSystem &operator=(const ParticleSystem &) = delete;

	virtual void update(float dt);
	virtual void reset();
    virtual void emit();

	virtual size_t getCount() const { return m_particles.m_count; }
	virtual size_t getAliveCount() const { return m_particles.m_count_alive; }

	void toggleUpdate() { do_update = !do_update; }
	void toggleEmit() { do_emit = !do_emit; }
	void toggleSort() { do_sort = !do_sort; }
    bool getUpdate(){ return do_update; }

	void addEmitter(std::shared_ptr<ParticleEmitter> em) { m_emitters.push_back(em); }
	void addUpdater(std::shared_ptr<ParticleUpdater> up) { m_updaters.push_back(up); }

	ParticleData *finalData() { return &m_particles; }

protected:
	ParticleData m_particles;
	std::shared_ptr<Camera> m_camera;

	size_t m_count;
	bool do_update = true, do_emit = true, do_sort = true;

	std::vector<std::shared_ptr<ParticleEmitter>> m_emitters;
	std::vector<std::shared_ptr<ParticleUpdater>> m_updaters;

	
};

#endif //PARTICLESYSTEM