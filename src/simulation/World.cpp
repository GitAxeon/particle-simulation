#include "World.h"

namespace ParticleSimulation
{
    World::World(Vec2 worldSize)
    {
        Info = WorldInfo(worldSize);
        m_WorldSize = worldSize;
        
        m_Particles.resize(worldSize.x * worldSize.y, Particle(Element::Null));

        m_ParticleDatabase.Insert(Particle(Element::Sand, RGBA(194, 178, 128)));
        m_ParticleDatabase.Insert(Particle(Element::Water, RGBA(0, 0, 255)));
        m_ParticleDatabase.Insert(Particle(Element::Rock, RGBA(90, 77, 65)));
        m_ParticleDatabase.Insert(Particle(Element::Null, RGBA(0, 0, 0, 255)));
    }

    void World::Update()
    {  
        m_WorldChanged = false;

        if(m_UpdateWorld)
        {
            bool worldChanged = false;

            for(Index i = Info.GetMaxIndex(); i >= 0; --i)
            {
                if(m_Particles[i].ID == Element::Null)
                    continue;

                bool change = m_Particles[i].Update(*this, Info.IndexToPosition(i));

                if(change)
                    worldChanged = true;
            }
            
            m_UpdateWorld = worldChanged;
            m_WorldChanged = true;
        }
    }

    bool World::PlaceParticle(ElementID id, Vec2 position)
    {
        if(!Info.IsValidPosition(position))
            return false;

        Index index = Info.PositionToIndex(position);
        
        if(id == m_Particles[index].ID)
            return false;

        m_Particles[index] = m_ParticleDatabase.Get(id);

        m_UpdateWorld = true;

        return true;
    }

    bool World::SwapParticle(Vec2 positionA, Vec2 positionB)
    {
        if(!Info.IsValidPosition(positionA) || !Info.IsValidPosition(positionB))
            return false;

        Index indexA = Info.PositionToIndex(positionA);
        Index indexB = Info.PositionToIndex(positionB);

        std::swap(m_Particles[indexA], m_Particles[indexB]);

        m_UpdateWorld = true;

        return true;
    }

    ElementID World::ParticleAt(Vec2 position) const
    {
        if(!Info.IsValidPosition(position))
            return Element::Unknown;
            
        Index index = Info.PositionToIndex(position);

        return m_Particles[index].ID;
    }

    bool World::IsEmpty(Vec2 position) const
    {
        return Info.IsValidPosition(position) && ParticleAt(position) == Element::Null;
    }
}