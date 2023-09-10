#pragma once

#include "World.h"
#include "SDL3/SDL.h"

namespace ParticleSimulation
{
    class Renderer
    {
    public:
        Renderer(World& world, SDL_Renderer* renderer);
        void UpdateTexture();
        void Render();
    private:
        World& m_World;
        SDL_Renderer* m_SDLRenderer;

        SDL_Texture* m_Texture = nullptr;
        ColorMapper m_ColorMapper;
    };
}