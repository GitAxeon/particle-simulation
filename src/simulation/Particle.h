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

            Temperature = 0.f;
            Flammability = 0.f;
            CorrosionResistance = 0.f;

            Behaviour = nullptr;
        }

        ParticleID Id;
        RGBA Color;
        StateOfMatter MatterState;
        bool Sleep;

        float Temperature;
        float Flammability;
        float CorrosionResistance;

        ParticleBehaviour* Behaviour;
    };
}