#pragma once

#include "WorldInfo.h"
#include "ParticleDatabase.h"

#include <vector>

namespace ParticleSimulation
{
    class Particle;

    class World 
    {
    public:
        World(Vec2 worldSize = Vec2(640, 360));
        
        void Update();
        
        bool PlaceParticle(ElementID, Vec2 position);
        bool SwapParticle(Vec2 positionA, Vec2 positionB);

        bool IsEmpty(Vec2 position) const;

        ElementID ParticleAt(Vec2 position) const;

        std::vector<Particle>& GetParticles() { return m_Particles; }
        
        bool WorldChanged() const { return m_WorldChanged; }

    public:
        WorldInfo Info;
    
    private:
        Vec2 m_WorldSize;
        std::vector<Particle> m_Particles;
        ParticleDatabase m_ParticleDatabase;

        bool m_WorldChanged = false;
        bool m_UpdateWorld = false;
    };
}