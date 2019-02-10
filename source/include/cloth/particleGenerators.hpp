/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/
#ifndef GEN_HPP
#define GEN_HPP

#include <cloth/particleData.hpp>

class ParticleGenerator{
public:
	ParticleGenerator() { }
	virtual ~ParticleGenerator() { }

	virtual void generate(float dt, ParticleData *p, size_t start_Id, size_t end_id) = 0;
};

class GridPosGen: public ParticleGenerator {
public:
	glm::fvec4 m_pos;
	glm::fmat4 m_rot;
	int m_w;
	int m_h;
	float m_d;

	GridPosGen() : m_pos{0.0f}, m_rot{1.0f}, m_w{3}, m_h{3}, m_d{1} {}

	virtual void generate(float dt, ParticleData *p, size_t start_id, size_t end_id) override;
};

class PrevPosGen: public ParticleGenerator {
public:
    virtual void generate(float dt, ParticleData *p, size_t start_id, size_t end_id) override;
};

class SpringGen : public ParticleGenerator {
	virtual void generate(float dt, ParticleData *p, size_t start_id, size_t end_id) override;

};

class MeshMassGen : public ParticleGenerator {
public:
	float m_total_mass;
	virtual void generate(float dt, ParticleData *p, size_t start_id, size_t end_id) override;

};

#endif //GEN_HPP