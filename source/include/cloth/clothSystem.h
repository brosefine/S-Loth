//
// Created by anny on 27.12.18.
//

#ifndef RTR_CLOTHSYSTEM_H
#define RTR_CLOTHSYSTEM_H

#include <cloth/particleSystem.hpp>

class ClothSystem : public ParticleSystem {
public:
    ClothSystem(size_t maxCount, std::shared_ptr<Camera> cam);

    void update(float dt) override;

};


#endif //RTR_CLOTHSYSTEM_H
