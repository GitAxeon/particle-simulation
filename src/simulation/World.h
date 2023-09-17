#pragma once

#include "WorldInfo.h"
#include "ParticleDatabase.h"

#include <vector>

namespace ParticleSimulation
{
    class World 
    {
    public:
        World(Vec2 worldSize = Vec2(640, 360));
        
        void Update();
        
        bool PlaceParticle(ParticleData particle, Vec2 position);
        bool SwapParticle(Vec2 positionA, Vec2 positionB);

        bool IsEmpty(Vec2 position) const;

        ParticleData ParticleAt(Vec2 position) const;

        const ParticleDatabase& GetParticleDatabase() const { return m_ParticleDatabase; } 
        std::vector<ParticleData>& GetParticles() { return m_Particles; }
        
        bool WorldChanged() const { return m_WorldChanged; }

    public:
        WorldInfo Info;
    
    private:
        Vec2 m_WorldSize;
        std::vector<ParticleData> m_Particles;
        ParticleDatabase m_ParticleDatabase;

        bool m_WorldChanged = false;
        bool m_UpdateWorld = false;
    };
}