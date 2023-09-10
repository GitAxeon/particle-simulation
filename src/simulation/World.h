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

        bool IsEmpty(Vec2 position) const;

        std::vector<Particle*>& GetParticles() { return m_Particles; }
        
        bool WorldChanged() const { return m_WorldChanged; }

    public:
        WorldInfo Info;
    
    private:
        Vec2 m_WorldSize;
        std::vector<Particle*> m_Particles;
        bool m_WorldChanged = false;
    };
}