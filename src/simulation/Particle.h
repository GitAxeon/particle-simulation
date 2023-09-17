#pragma once

#include "../RGBA.h"
#include "Math.h"

namespace ParticleSimulation
{   
    using ParticleID = unsigned int;
    enum class StateOfMatter { Unknown, Solid, Gas, Liquid };
    
    class ParticleBehaviour;
    
    struct ParticleData
    {
        ParticleData()
        {
            Id = 666;
            Color = RGBA(255, 0, 255);
            MatterState = StateOfMatter::Unknown;
            Sleep = true;

            Behaviour = nullptr;
        }

        ParticleID Id;
        RGBA Color;
        StateOfMatter MatterState;
        bool Sleep;

        ParticleBehaviour* Behaviour;
    };
}