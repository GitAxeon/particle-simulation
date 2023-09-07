#pragma once

#include "World.h"
#include "SDL3/SDL.h"

namespace ParticleSimulation
{
    class Renderer
    {
    public:
        Renderer(World& world, SDL_Renderer* renderer) : m_World(world), m_SDLRenderer(renderer)
        {

        }

        void Render();

    private:
        World& m_World;
        SDL_Renderer* m_SDLRenderer;
    };
}