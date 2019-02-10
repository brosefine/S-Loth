/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/

#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include "headers.hpp"

class ParticleData {
public:

	
	std::unique_ptr<glm::vec4[]> m_pos;
	std::unique_ptr<glm::vec4[]> m_pos_prev;
	std::unique_ptr<glm::vec4[]> m_col;
	std::unique_ptr<glm::vec4[]> m_acc;
    std::unique_ptr<float[]> m_mass;
	std::unique_ptr<glm::vec4[]> m_normal;
	std::unique_ptr<glm::vec4[]> m_uv;
	std::unique_ptr<bool[]>  m_alive;

    // cloth stuff
	std::shared_ptr<std::vector<unsigned int>> m_indices;
    std::shared_ptr<std::vector<glm::vec3>> m_struct_con;
    std::shared_ptr<std::vector<glm::vec3>> m_shear_con;
    std::shared_ptr<std::vector<glm::vec3>> m_bend_con;

	size_t m_count{0};
	size_t m_count_alive{0};

public:
	ParticleData() { }
	explicit ParticleData(size_t maxCount) { generate(maxCount); }	// explicit -> PD par{x} is okay, PD par = {x} not
	~ParticleData() { }
	ParticleData(const ParticleData &) = delete;					// these c'tors cannot be used
	ParticleData &operator=(const ParticleData &) = delete;

	void generate(size_t maxSize);									// initializes all ptr with maxSize-d arrays
	void wake(size_t id);											// wakes given particle

};

#endif //PARTICLES_HPP