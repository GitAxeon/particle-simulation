#pragma once

#include "Math.h"

namespace ParticleSimulation
{
    enum class ParticleID 
    {
        Unknown, Null, Sand, Rock, Water
    };

    struct Particle
    {
        ParticleID ID;

        MMath::f32Vec2 Velocity;
    };
}