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
        m_WorldChanged = false;

        if(m_UpdateWorld)
        {
            bool worldChanged = false;

            for(Index i = Info.GetMaxIndex(); i >= 0; --i)
            {
                if(m_Particles[i]->GetType() == ParticleType::NullParticle)
                    continue;

                bool change = m_Particles[i]->Update(*this, Info.IndexToPosition(i));

                if(change)
                    worldChanged = true;
            }
            
            m_UpdateWorld = worldChanged;
            m_WorldChanged = true;
        }
    }

    bool World::PlaceParticle(Particle* particle, Vec2 position)
    {
        if(!Info.IsValidPosition(position))
            return false;

        Index index = Info.PositionToIndex(position);
        
        if(particle->GetType() == m_Particles[index]->GetType())
            return false;

        delete m_Particles[index];

        m_Particles[index] = particle;

        m_UpdateWorld = true;

        return true;
    }

    ParticleType World::ParticleAt(Vec2 position) const
    {
        if(!Info.IsValidPosition(position))
            return ParticleType::Unknown;
            
        Index index = Info.PositionToIndex(position);

        return m_Particles[index]->GetType();
    }

    bool World::IsEmpty(Vec2 position) const
    {
        return Info.IsValidPosition(position) && ParticleAt(position) == ParticleType::NullParticle;
    }
}