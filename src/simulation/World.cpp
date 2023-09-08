#include "World.h"

namespace ParticleSimulation
{
    World::World(Vec2 worldSize)
    {
        Info = WorldInfo(worldSize);
        
        m_Particles.resize(worldSize.x * worldSize.y);
        std::fill(m_Particles.begin(), m_Particles.end(), NullParticle());
    }

    void World::Update()
    {  
        auto it = m_Particles.rbegin();
        size_t index = 0;

        for(; it != m_Particles.rend(); it++)
        {
            it->Update(m_Particles, Info.IndexToPosition(index));

            ++index;
        }
    }
}