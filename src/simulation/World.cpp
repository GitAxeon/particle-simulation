#include "World.h"

#include "DefaultBehaviours.h"

namespace ParticleSimulation
{
    World::World(Vec2 worldSize)
    {
        Info = WorldInfo(worldSize);
        m_WorldSize = worldSize;
        
        m_Particles.resize(worldSize.x * worldSize.y, m_ParticleDatabase.GetParticle(0));

        m_ParticleDatabase.InsertBehaviour("Sand", new SandBehaviour);
        m_ParticleDatabase.InsertBehaviour("Water", new WaterBehaviour);
        m_ParticleDatabase.InsertBehaviour("Acid", new AcidBehaviour);

        ParticleData sandData;
        sandData.Id = 1;
        sandData.Color = RGBA(194, 178, 128);
        sandData.MatterState = StateOfMatter::Solid;
        sandData.Sleep = false;
        sandData.Flammability = 0.f;
        sandData.Temperature = 0.f;
        sandData.CorrosionResistance = 0.4f;
        sandData.Behaviour = m_ParticleDatabase.GetBehaviour("Sand");

        ParticleInfo sand;
        sand.Name = "Sand";
        sand.Data = sandData;

        m_ParticleDatabase.InsertParticle(sand);

        ParticleData waterData;
        waterData.Id = 2;
        waterData.Color = RGBA(0, 0, 255);
        waterData.MatterState = StateOfMatter::Liquid;
        waterData.Sleep = false;
        waterData.Flammability = 0.f;
        waterData.Temperature = 0.f;
        waterData.CorrosionResistance = 0.3f;
        waterData.Behaviour = m_ParticleDatabase.GetBehaviour("Water");

        ParticleInfo water;
        water.Name = "Water";
        water.Data = waterData;

        m_ParticleDatabase.InsertParticle(water);

        ParticleData rockData;
        rockData.Id = 3;
        rockData.Color = RGBA(90, 77, 65);
        rockData.MatterState = StateOfMatter::Solid;
        rockData.Sleep = true;
        rockData.Flammability = 0.f;
        rockData.Temperature = 0.f;
        rockData.CorrosionResistance = 0.78f;
        rockData.Behaviour = nullptr;

        ParticleInfo rock;
        rock.Name = "Rock";
        rock.Data = rockData;

        m_ParticleDatabase.InsertParticle(rock);

        ParticleData woodData;
        woodData.Id = 4;
        woodData.Color = RGBA(186, 140, 99);
        woodData.MatterState = StateOfMatter::Solid;
        woodData.Sleep = true;
        woodData.Flammability = 0.8f;
        woodData.Temperature = 0.f;
        woodData.CorrosionResistance = 0.2f;
        woodData.Behaviour = nullptr;

        ParticleInfo wood;
        wood.Name = "Wood";
        wood.Data = woodData;

        m_ParticleDatabase.InsertParticle(wood);

        ParticleData acidData;
        acidData.Id = 5;
        acidData.Color = RGBA(118, 187, 104);
        acidData.MatterState = StateOfMatter::Liquid;
        acidData.Sleep = true;
        acidData.Flammability = 0.7f;
        acidData.Temperature = 0.f;
        acidData.CorrosionResistance = 1.f;
        acidData.Behaviour = m_ParticleDatabase.GetBehaviour("Acid");

        ParticleInfo acid;
        acid.Name = "Acid";
        acid.Data = acidData;

        m_ParticleDatabase.InsertParticle(acid);

        ParticleData stainlesStell;
        stainlesStell.Id = 6;
        stainlesStell.Color = RGBA(180,189,199);
        stainlesStell.MatterState = StateOfMatter::Solid;
        stainlesStell.Sleep = true;
        stainlesStell.Flammability = 0.f;
        stainlesStell.Temperature = 0.f;
        stainlesStell.CorrosionResistance = 1.f;
        stainlesStell.Behaviour = nullptr;

        ParticleInfo ssteel;
        ssteel.Name = "Stainless steel";
        ssteel.Data = stainlesStell;

        m_ParticleDatabase.InsertParticle(ssteel);
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
            return m_ParticleDatabase.GetParticle(0);
            
        Index index = Info.PositionToIndex(position);

        return m_Particles[index];
    }

    bool World::IsEmpty(Vec2 position) const
    {
        return Info.IsValidPosition(position) && ParticleAt(position).Id == 0;
    }
}