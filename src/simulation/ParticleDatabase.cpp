#include "ParticleDatabase.h"

namespace ParticleSimulation
{
    ParticleDatabase::ParticleDatabase()
    {

        ParticleData nulldata;
        nulldata.Id = 0;
        nulldata.Color = RGBA(0, 0, 0);
        nulldata.MatterState = StateOfMatter::Unknown;
        nulldata.Sleep = true;
        
        nulldata.Flammability = 0.f;
        nulldata.Temperature = 0.f;
        nulldata.CorrosionResistance = 1.f;
        
        nulldata.Behaviour = nullptr;

        ParticleInfo NullParticle;
        NullParticle.Name = "Null";
        NullParticle.Data = nulldata;

        InsertParticle(NullParticle);
    }

    bool ParticleDatabase::InsertParticle(const ParticleInfo& info)
    {
        auto result = m_ParticleDatabase.insert(std::pair(info.Data.Id, info));

        return result.second;
    }

    ParticleData ParticleDatabase::GetParticle(ParticleID id) const
    {
        auto result = m_ParticleDatabase.find(id);

        if(result != m_ParticleDatabase.end())
            return result->second.Data;
        else
            return m_ParticleDatabase.at(0).Data;
    }

    bool ParticleDatabase::InsertBehaviour(const std::string& name, ParticleBehaviour* behaviour)
    {
        auto result = m_BehaviourDatabase.insert(std::pair(name, behaviour));

        return result.second;
    }

    ParticleBehaviour* ParticleDatabase::GetBehaviour(const std::string& name) const
    {
        auto result = m_BehaviourDatabase.find(name);

        if(result != m_BehaviourDatabase.end())
            return result->second;
        else
            return nullptr;
    }
}