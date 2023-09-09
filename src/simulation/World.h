#pragma once

#include "WorldInfo.h"
#include "Particle.h"

#include <vector>

namespace ParticleSimulation
{
    class Particle;

    class World 
    {
    public:
        World(Vec2 worldSize = Vec2(640, 360));
        ~World();

        void Update();
        
        bool PlaceParticle(Particle* particle, Vec2 position);

        std::vector<Particle*>& GetParticles() { return m_Particles; }
        

    public:
        WorldInfo Info;
    
    private:
        Vec2 m_WorldSize;
        std::vector<Particle*> m_Particles;
    };
}