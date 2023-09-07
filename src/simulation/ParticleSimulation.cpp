#include "ParticleSimulation.h"

namespace ParticleSimulation
{
    World::World(int width, int height) : m_Width(width), m_Height(height)
    {
        m_Particles.resize(width * height);

        std::fill(m_Particles.begin(), m_Particles.end(), NullParticle());

        // for(auto elem : m_Particles)
        // {
        //     std::cout << elem.GetColor() << std::endl;
        // }
    }

    void World::Update()
    {
        for(auto particle : m_Particles)
        {
            particle.Update(m_Particles);
        }
    }
}