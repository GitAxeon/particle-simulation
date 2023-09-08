#pragma once

#include "World.h"

namespace ParticleSimulation
{
    class UserInterface
    {
    public:
        UserInterface(World& world) : m_World(world) { };

        void HandleInput();

    private:
        World& m_World;
    };
}