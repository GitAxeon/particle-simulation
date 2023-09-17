#include "World.h"

#include "DefaultBehaviours.h"

namespace ParticleSimulation
{
    World::World(Vec2 worldSize)
    {
        Info = WorldInfo(worldSize);
        m_WorldSize = worldSize;
        
        m_Particles.resize(worldSize.x * worldSize.y, m_ParticleDatabase.Get(0));

        ParticleData sandData;
        sandData.Id = 1;
        sandData.Color = RGBA(194, 178, 128);
        sandData.Behaviour = new SandBehaviour;
        sandData.MatterState = StateOfMatter::Solid;
        sandData.Sleep = false;

        ParticleInfo sand;
        sand.Name = "Sand";
        sand.Data = sandData;

        m_ParticleDatabase.Insert(sand);

        ParticleData waterData;
        waterData.Id = 2;
        waterData.Color = RGBA(0, 0, 255);
        waterData.Behaviour = new WaterBehaviour;
        waterData.MatterState = StateOfMatter::Liquid;
        waterData.Sleep = false;

        ParticleInfo water;
        water.Name = "Water";
        water.Data = waterData;

        m_ParticleDatabase.Insert(water);

        ParticleData rockData;
        rockData.Id = 3;
        rockData.Color = RGBA(90, 77, 65);
        rockData.Behaviour = nullptr;
        rockData.MatterState = StateOfMatter::Solid;
        rockData.Sleep = true;

        ParticleInfo rock;
        rock.Name = "Rock";
        rock.Data = rockData;

        m_ParticleDatabase.Insert(rock);
        
        // m_ParticleDatabase.Insert(Particle(Element::Sand, RGBA(194, 178, 128)));

        // m_ParticleDatabase.Insert(Particle(Element::Water, RGBA(0, 0, 255)));
        
        // m_ParticleDatabase.Insert(Particle(Element::Rock, RGBA(90, 77, 65)));
        
        // m_ParticleDatabase.Insert(Particle(Element::Null, RGBA(0, 0, 0, 255)));
    }

    void World::Update()
    {  
        m_WorldChanged = false;

        if(m_UpdateWorld)
        {
            bool worldChanged = false;

            for(Index i = Info.GetMaxIndex(); i >= 0; --i)
            {
                if(m_Particles[i].Behaviour == nullptr)
                    continue;

                bool change = m_Particles[i].Behaviour->Update(*this, m_Particles[i], Info.IndexToPosition(i));

                if(change)
                    worldChanged = true;
            }
            
            m_UpdateWorld = worldChanged;
            m_WorldChanged = true;
        }
    }

    bool World::PlaceParticle(ParticleData particle, Vec2 position)
    {
        if(!Info.IsValidPosition(position))
            return false;

        Index index = Info.PositionToIndex(position);
        
        m_Particles[index] = particle;

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

    ParticleData World::ParticleAt(Vec2 position) const
    {
        if(!Info.IsValidPosition(position))
            return m_ParticleDatabase.Get(0);
            
        Index index = Info.PositionToIndex(position);

        return m_Particles[index];
    }

    bool World::IsEmpty(Vec2 position) const
    {
        return Info.IsValidPosition(position) && ParticleAt(position).Id == 0;
    }
}