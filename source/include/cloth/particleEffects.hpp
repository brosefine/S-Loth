/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/
#ifndef PARTICLEEFFECT_HPP
#define PARTICLEEFFECT_HPP

#include <cloth/headers.hpp>
#include <cloth/particleHeaders.hpp>
#include <camera/Camera.h>
#include <set>
#include <mutex>

class ParticleEffect {
public:
	ParticleEffect(){}
	virtual ~ParticleEffect(){}

	virtual void init(size_t numParticles, Camera* cam) = 0;
	virtual void initRenderer() { m_rend->generate(m_sys.get());}
	virtual void reset() { m_sys->reset(); m_fixed.clear();}
	virtual void clean() { m_rend->destroy();}
	virtual void toggleUpdate() { m_sys->toggleUpdate(); }
	virtual void toggleEmit() { m_sys->toggleEmit(); }
    bool getUpdate(){ return m_sys->getUpdate(); };

    virtual void update(float dt) = 0;
	virtual void cpuUpdate(float dt) { m_sys->update(dt);}
	virtual void gpuUpdate() { m_rend->update();}
	virtual void render() { m_rend->render();}
    virtual void emit() { m_sys->emit();}

	virtual int numAllParticles() { return m_sys->getCount();}
	virtual int numAliveParticles() { return m_sys->getAliveCount();};

	virtual void fixedParticles(unsigned int i) { m_fixed.insert(i); };
    virtual void fixedAllParticles() { for(int i = 0; i < numAllParticles(); ++i){
        fixedParticles(i);
      }}
    virtual std::vector<glm::vec3> getfixedParticles() { std::vector<glm::vec3> result;
      for(auto i : m_fixed){ result.push_back(glm::vec3(m_sys->finalData()->m_pos[i])); }
      return result;
    }
	virtual void movingParticles(unsigned int i) { m_fixed.erase(i); };
    virtual void movingAllParticles() { m_fixed.clear(); }

protected:
	std::shared_ptr<Camera> m_cam;
	std::shared_ptr<ParticleSystem> m_sys;
	std::shared_ptr<ParticleRenderer> m_rend = std::make_shared<ParticleRenderer> ();
    std::set<unsigned int> m_fixed;


};

class ClothEffect : public ParticleEffect {
public:
	ClothEffect(){}
	~ClothEffect(){}

	void init(size_t numParticles, Camera* cam) override;
	void update(float dt) override;
    void reset() override;
    int findClosest(glm::vec3 ray);
    void setDrag(glm::vec3 ray);
    void releaseDrag();

    glm::fvec4 m_gridPos;
    glm::fmat4 m_gridRot;
    int m_gridW;
    int m_gridH;
    float m_gridD;
	float m_damp;
	float m_kStruct;
	float m_kShear;
	float m_kBend;
    float m_minStretch;
    float m_maxStretch;
    float m_sphereRad;
    float m_sphereFric;
    glm::vec3 m_cubePos;
    float m_cubeDim;
    glm::vec3 m_spherePos;
    int m_stretchIter;
    float m_collisionDist;
    float m_mass;
	float m_res;
    glm::vec3 m_windVec;

    glm::vec4 m_dragParticle{0};
    std::mutex m_dragMutex;

    bool m_wind = false;
    bool m_gravity = true;
    bool m_structure = true;
    bool m_shear = true;
    bool m_bend = true;
    bool m_stretch = true;
    bool m_sphere = false;
    bool m_cube = false;
	bool m_collision = false;

private:
	std::shared_ptr<GridPosGen> m_posGen;
    std::shared_ptr<PrevPosGen> m_prevGen;
    std::shared_ptr<SpringGen> m_springGen;
    std::shared_ptr<MeshMassGen> m_massGen;

    std::shared_ptr<GravityUpdater> m_gravUp;
    std::shared_ptr<VerletPosUpdater> m_posUp;
    std::shared_ptr<SpringColourUpdater> m_colUp;
    std::shared_ptr<SpringUpdater> m_structUp;
    std::shared_ptr<SpringUpdater> m_shearUp;
    std::shared_ptr<SpringUpdater> m_bendUp;
    std::shared_ptr<StretchUpdater> m_stretchUp;
	std::shared_ptr<NormalUpdater> m_normUp;
    std::shared_ptr<SphereCollisionUpdater> m_sphereUp;
	std::shared_ptr<ClothCollisionUpdater> m_collisionUp;
	std::shared_ptr<GroundCollisionUpdater> m_groundUp;
    std::shared_ptr<CubeCollisionUpdater> m_cubeUp;
    std::shared_ptr<WindForceUpdater> m_windUp;
	std::shared_ptr<AirResistanceUpdater> m_resUp;

};
#endif