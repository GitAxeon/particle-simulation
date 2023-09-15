#include "ParticleDatabase.h"

namespace ParticleSimulation
{
    bool ParticleDatabase::Insert(Particle p)
    {
        auto result = m_Database.insert(std::pair(p.ID, p));

        return result.second;
    }

    Particle ParticleDatabase::Get(ElementID id) const
    {
        auto result = m_Database.find(id);

        if(result != m_Database.end())
            return result->second;
        else
            return Particle(Element::Null);
    }
}