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
        // auto it = m_Particles.rbegin();
        // size_t index = Info.GetMaxIndex();
        
        // if(m_WorldChanged)
        // {
        //     bool worldChanged = false;
            
        //     for(; it != m_Particles.rend(); it++)
        //     {
        //         bool change = (*it)->Update(*this, Info.IndexToPosition(index));

        //         if(change)
        //             worldChanged = true;

        //         --index;
        //     }

        //     m_WorldChanged = worldChanged;
        // }

        if(m_WorldChanged)
        {
            bool worldChanged = false;

            for(Index i = Info.GetMaxIndex(); i >= 0; --i)
            {
                bool change = m_Particles[i]->Update(*this, Info.IndexToPosition(i));

                if(change)
                    worldChanged = true;
            }
            
            m_WorldChanged = worldChanged;
        }
    }

    bool World::PlaceParticle(Particle* particle, Vec2 position)
    {
        if(!Info.IsValidPosition(position))
            return false;

        Index index = Info.PositionToIndex(position);
        
        delete m_Particles[index];

        m_Particles[index] = particle;

        m_WorldChanged = true;

        return true;
    }
}