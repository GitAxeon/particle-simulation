#pragma once

#include "Particle.h"

#include <vector>

class ParticleSimulation
{
public:
    ParticleSimulation() = delete;
    ParticleSimulation(int width, int height);

    void Step();

private:
    std::vector<Particle> m_Particles;

    int m_Width;
    int m_Height;
};