#pragma once

#include "Particle.h"

#include <map>
#include <string>

namespace ParticleSimulation
{   
    struct ParticleInfo 
    {
        std::string Name;
        ParticleData Data;
    };

    class ParticleDatabase
    {
    public:
        ParticleDatabase();
        bool Insert(const ParticleInfo& info);
        ParticleData Get(ParticleID id) const;

    private:
        std::map<ParticleID, ParticleInfo> m_Database;
    };
}