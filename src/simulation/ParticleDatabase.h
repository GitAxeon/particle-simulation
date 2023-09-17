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

        bool InsertParticle(const ParticleInfo& info);
        ParticleData GetParticle(ParticleID id) const;
        std::map<ParticleID, ParticleInfo>& GetParticles() { return m_ParticleDatabase; }

        bool InsertBehaviour(const std::string& name, ParticleBehaviour* behaviour);
        ParticleBehaviour* GetBehaviour(const std::string& name) const;

    private:
        std::map<ParticleID, ParticleInfo> m_ParticleDatabase;
        std::map<std::string, ParticleBehaviour*> m_BehaviourDatabase;
    };
}