#pragma once

#include "Particle.h"

#include <set>

namespace ParticleSimulation
{
    class ParticleDatabase
    {
    public:
        ParticleDatabase();
        ~ParticleDatabase();

    private:
        std::set<ParticleType, Particle> m_Database;
    };
}