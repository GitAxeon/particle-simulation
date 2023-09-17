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
        nulldata.Behaviour = nullptr;

        ParticleInfo NullParticle;
        NullParticle.Name = "Null";
        NullParticle.Data = nulldata;

        m_Database.insert(std::pair(0, NullParticle));
    }

    bool ParticleDatabase::Insert(const ParticleInfo& info)
    {
        auto result = m_Database.insert(std::pair(info.Data.Id, info));

        return result.second;
    }

    ParticleData ParticleDatabase::Get(ParticleID id) const
    {
        auto result = m_Database.find(id);

        if(result != m_Database.end())
            return result->second.Data;
        else
            return m_Database.at(0).Data;
    }
}