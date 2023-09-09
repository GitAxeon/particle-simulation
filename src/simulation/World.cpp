#include "World.h"
#include "Particle.h"

namespace ParticleSimulation
{
    World::World(Vec2 worldSize)
    {
        Info = WorldInfo(worldSize);
        m_WorldSize = worldSize;
        
        m_Particles.resize(worldSize.x * worldSize.y, nullptr);

        
        for(size_t i = 0; i < m_Particles.size(); i++)
        {
            m_Particles[i] = new NullParticle;
        }

        // delete m_Particles[0];
        // m_Particles[0] = new Sand;
    }

    World::~World()
    {
        for(auto ptr : m_Particles)
        {
            delete ptr;
        }
    }

    void World::Update()
    {  
        auto it = m_Particles.rbegin();
        size_t index = Info.GetMaxIndex();

        for(; it != m_Particles.rend(); it++)
        {
            (*it)->Update(*this, Info.IndexToPosition(index));

            --index;
        }
    }

    bool World::PlaceParticle(Particle* particle, Vec2 position)
    {
        if(!Info.IsValidPosition(position))
            return false;

        Index index = Info.PositionToIndex(position);
        
        delete m_Particles[index];

        m_Particles[index] = particle;

        return true;
    }
}