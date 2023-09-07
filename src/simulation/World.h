#pragma once

#include "Particle.h"

#include <vector>

namespace ParticleSimulation
{
    class World 
    {
    public:
        World(int width = 640, int height = 360);

        void Update();

    private:
        std::vector<Particle> m_Particles;

        int m_Width;
        int m_Height;
    };
}