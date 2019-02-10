//
// Created by anny on 27.12.18.
//

#include <cloth/clothSystem.h>

ClothSystem::ClothSystem(size_t maxCount, std::shared_ptr<Camera>cam)
  : ParticleSystem(maxCount, cam) {}

void ClothSystem::update(float dt) {
  if(do_update) {

    if(getAliveCount() > 0){
      for (size_t i = 0; i < m_count; ++i){
        m_particles.m_acc[i] = glm::vec4(0.0f);
      }

      for(auto& up : m_updaters) {
        up->update(dt, &m_particles);
      }

    }
  }
}