#define GLM_ENABLE_EXPERIMENTAL
/******************************************************************************
 * Concept & Code from  Bartłomiej Filipek									  *
 * https://github.com/fenbf/particles 										  *
 * https://www.bfilipek.com/2014/03/three-particle-effects.html				  *
 ******************************************************************************/
#include <cloth/particleEffects.hpp>
#include <cloth/clothSystem.h>


void ClothEffect::reset() {
  if(m_sys && m_gridW * m_gridH != m_sys->getCount()) m_fixed.clear();
  m_sys.reset(new ClothSystem(m_gridW * m_gridH, m_cam));
  m_rend.reset(new ParticleRenderer());
  m_posGen->m_pos = m_gridPos;
  m_posGen->m_rot = m_gridRot;
  m_posGen->m_w = m_gridW;
  m_posGen->m_h = m_gridH;
  m_posGen->m_d = m_gridD;
  m_massGen->m_total_mass = m_mass;

  m_structUp.reset(new SpringUpdater(m_sys->finalData()->m_struct_con));
  m_shearUp.reset(new SpringUpdater(m_sys->finalData()->m_shear_con));
  m_bendUp.reset(new SpringUpdater(m_sys->finalData()->m_bend_con));

  m_colUp->m_min = m_minStretch;
  m_colUp->m_max = m_maxStretch;
  m_colUp->m_minCol = glm::vec3(0, 1, 0);
  m_colUp->m_maxCol = glm::vec3(1, 0, 0);
  m_posUp->m_damp = m_damp;
  m_structUp->m_k = m_kStruct;
  m_shearUp->m_k = m_kShear;
  m_bendUp->m_k = m_kBend;
  m_stretchUp->m_min = m_minStretch;
  m_stretchUp->m_max = m_maxStretch;
  m_stretchUp->m_iter = m_stretchIter;
  m_sphereUp->m_r = m_sphereRad;
  m_sphereUp->m_pos = m_spherePos;
  m_sphereUp->m_f = m_sphereFric;
  m_cubeUp->m_min = m_cubePos - glm::vec3(m_cubeDim / 2.f);
  m_cubeUp->m_max = m_cubePos + glm::vec3(m_cubeDim / 2.f);
  m_collisionUp->m_dist = m_gridD * m_collisionDist;
  m_windUp->m_wind = m_windVec;
  m_resUp->m_a = m_res;

  if(m_structure) m_sys->addUpdater(m_structUp);
  if(m_shear) m_sys->addUpdater(m_shearUp);
  if(m_bend) m_sys->addUpdater(m_bendUp);
  if(m_gravity) m_sys->addUpdater(m_gravUp);
  if(m_wind) m_sys->addUpdater(m_windUp);
  m_sys->addUpdater(m_resUp);
  m_sys->addUpdater(m_posUp);
  if(m_stretch) m_sys->addUpdater(m_stretchUp);
  m_sys->addUpdater(m_colUp);
  if(m_collision) m_sys->addUpdater(m_collisionUp);
  if(m_sphere) m_sys->addUpdater(m_sphereUp);
  if(m_cube) m_sys->addUpdater(m_cubeUp);
  m_sys->addUpdater(m_groundUp);
  m_sys->addUpdater(m_normUp);

  auto emmit = std::make_shared<ParticleEmitter>(m_gridW * m_gridH);
  emmit->addGenerator(m_posGen);
  emmit->addGenerator(m_prevGen);
  emmit->addGenerator(m_springGen);
  emmit->addGenerator(m_massGen);
  m_sys->addEmitter(emmit);

  //create mesh faces
  auto ind = m_sys->finalData()->m_indices;
  for(int h = 0; h < m_gridH - 1; ++h){
    for(int w = 0; w < m_gridW - 1; ++w) {
      unsigned int top_left = w % m_gridW + h * m_gridW;
      unsigned int top_right = top_left + 1;
      unsigned int bot_left = top_left + m_gridW;
      unsigned int bot_right = bot_left + 1;
      ind->push_back(top_left);
      ind->push_back(bot_right);
      ind->push_back(top_right);
      ind->push_back(top_left);
      ind->push_back(bot_left);
      ind->push_back(bot_right);
    }
  }

  //create springs
  auto struc = m_sys->finalData()->m_struct_con;
  for(int h = 0; h < m_gridH; ++h){
    for(int w = 0; w < m_gridW; ++w) {
      if(w < m_gridW - 1) {
        unsigned int left = w % m_gridW + h * m_gridW;
        unsigned int right = left + 1;
        struc->push_back(glm::fvec3(left, right, 0));
      }

      if(h < m_gridH - 1) {
        unsigned int top = w % m_gridW + h * m_gridW;
        unsigned int bottom = top + m_gridW;
        struc->push_back(glm::fvec3(top, bottom, 0));
      }
    }
  }

  auto shear = m_sys->finalData()->m_shear_con;
  for(int h = 0; h < m_gridH - 1; ++h){
    for(int w = 0; w < m_gridW - 1; ++w) {
      unsigned int top_left = w % m_gridW + h * m_gridW;
      unsigned int top_right = top_left + 1;
      unsigned int bot_left = top_left + m_gridW;
      unsigned int bot_right = bot_left + 1;
      shear->push_back(glm::fvec3(top_left, bot_right, 0));
      shear->push_back(glm::fvec3(top_right, bot_left, 0));

    }
  }

  auto bend = m_sys->finalData()->m_bend_con;
  for(int h = 0; h < m_gridH; ++h) {
    for (int w = 0; w < m_gridW; ++w) {
      if (w < m_gridW - 2) {
        unsigned int left = w % m_gridW + h * m_gridW;
        unsigned int right = left + 2;
        bend->push_back(glm::fvec3(left, right, 0));
      }
      if (h < m_gridH - 2) {
        unsigned int top = w % m_gridW + h * m_gridW;
        unsigned int bottom = top + 2 * m_gridW;
        bend->push_back(glm::fvec3(top, bottom, 0));
      }
    }
  }

  emit();

  auto uv = m_sys->finalData()->m_uv.get();
  for(int h = 0; h < m_gridH; ++h) {
    for (int w = 0; w < m_gridW; ++w) {
      float u = w / (float)m_gridW;
      float v = (h / (float)m_gridH);

      uv[h * m_gridW + w] = glm::vec4(u, v, 0, 0);
    }
  }

  m_collisionUp->init(m_sys->finalData());
  m_normUp->update(0.f, m_sys->finalData());
  initRenderer();

}

void ClothEffect::init(size_t numParticles, Camera *cam) {
  m_cam.reset(cam);

  m_posGen = std::make_shared<GridPosGen>();
  m_prevGen = std::make_shared<PrevPosGen>();
  m_springGen = std::make_shared<SpringGen>();
  m_massGen = std::make_shared<MeshMassGen>();

  m_colUp = std::make_shared<SpringColourUpdater>();
  m_gravUp = std::make_shared<GravityUpdater>();
  m_posUp = std::make_shared<VerletPosUpdater>();
  m_stretchUp = std::make_shared<StretchUpdater>();
  m_normUp = std::make_shared<NormalUpdater>();
  m_sphereUp = std::make_shared<SphereCollisionUpdater>();
  m_cubeUp = std::make_shared<CubeCollisionUpdater>();
  m_collisionUp = std::make_shared<ClothCollisionUpdater>();
  m_windUp = std::make_shared<WindForceUpdater>();
  m_groundUp = std::make_shared<GroundCollisionUpdater>();
  m_resUp = std::make_shared<AirResistanceUpdater>();

  m_groundUp->m_height = -20.f;

}

void ClothEffect::update(float dt) {
  auto pos = m_sys->finalData()->m_pos.get();
  for(unsigned int i = 0; i < m_sys->getCount(); ++i){
    if(m_fixed.count(i)){
      pos[i].w = 1.f;
    } else {
      pos[i].w = 0.f;
    }
  }

  m_posUp->m_damp = m_damp;
  m_structUp->m_k = m_kStruct;
  m_shearUp->m_k = m_kShear;
  m_bendUp->m_k = m_kBend;
  m_stretchUp->m_min = m_minStretch;
  m_stretchUp->m_max = m_maxStretch;
  m_sphereUp->m_f = m_sphereFric;
  m_collisionUp->m_dist = m_posGen->m_d * m_collisionDist;
  m_windUp->m_wind = m_windVec;
  m_colUp->m_min = m_minStretch;
  m_colUp->m_max = m_maxStretch;
  m_resUp->m_a = m_res;

  m_dragMutex.lock();
  if(glm::length(m_dragParticle) != 0) {
    //std::cout << m_dragParticle.x << "," << m_dragParticle.y << "," << m_dragParticle.z << "," << m_dragParticle.w << std::endl;
    m_sys->finalData()->m_pos[m_dragParticle.w].x = m_dragParticle.x;
    m_sys->finalData()->m_pos[m_dragParticle.w].y = m_dragParticle.y;
    m_sys->finalData()->m_pos[m_dragParticle.w].z = m_dragParticle.z;
  }
  m_dragMutex.unlock();
}

int ClothEffect::findClosest(glm::vec3 ray){
  auto pos = m_sys->finalData()->m_pos.get();
  float l = glm::length(ray);
  float dist = FLT_MAX, temp = 0;
  unsigned int result;
  for(unsigned int i = 0; i < m_sys->getCount(); ++i){
    temp = glm::length(glm::cross(ray, m_cam->getPosition() - glm::vec3(pos[i]))) / l;
    if(temp < dist){
      dist = temp;
      result = i;
    }
  }

  return result;
}

void ClothEffect::setDrag(glm::vec3 ray) {
  movingAllParticles();
  int index = findClosest(ray);
  m_dragParticle = m_sys->finalData()->m_pos[index];
  m_dragParticle.w = index;
  fixedParticles(index);
}

void ClothEffect::releaseDrag() {
  m_sys->finalData()->m_pos[m_dragParticle.w].w = 0;
  m_dragParticle = glm::vec4(0);
}
