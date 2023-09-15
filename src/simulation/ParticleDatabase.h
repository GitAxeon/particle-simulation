#pragma once

#include "Particle.h"
#include <map>

namespace ParticleSimulation
{   
    class ParticleDatabase
    {
    public:
        bool Insert(Particle);
        Particle Get(ElementID) const;

    private:
        std::map<ElementID, Particle> m_Database;
    };
}