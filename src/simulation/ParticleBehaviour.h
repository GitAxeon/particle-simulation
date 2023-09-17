#pragma once

#include "World.h"
#include "WorldInfo.h"

namespace ParticleSimulation
{
    class World;
    class ParticleData;
    
    class ParticleBehaviour
    {
    public:
        virtual bool Update(World& world, ParticleData& particle, Vec2 position) = 0;
        
        virtual ~ParticleBehaviour() { };
    };
}