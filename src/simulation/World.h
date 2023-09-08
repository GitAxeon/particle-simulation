#pragma once

#include "WorldInfo.h"
#include "Particle.h"

#include <vector>

namespace ParticleSimulation
{
    class World 
    {
    public:
        World(Vec2 worldSize = Vec2(640, 360));

        void Update();

        std::vector<Particle>& GetParticles() { return m_Particles; }

    public:
        WorldInfo Info;
    
    private:
        Vec2 m_worldSize;
        std::vector<Particle> m_Particles;
    };
}