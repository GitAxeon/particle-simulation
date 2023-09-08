#include "Renderer.h"

namespace ParticleSimulation
{
    Renderer::Renderer(World& world, SDL_Renderer* renderer) 
        : m_World(world), m_SDLRenderer(renderer)
    {
        Vec2 size = world.Info.GetSize();

        m_Texture = SDL_CreateTexture(
            renderer, 
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STREAMING,
            static_cast<int>(size.x), 
            static_cast<int>(size.y)
        );
    }

    void Renderer::Render()
    {  
        int pitch = static_cast<int>(m_World.Info.GetSize().x) * 4;
        void* pixels = nullptr;

        SDL_LockTexture(
            m_Texture,
            nullptr,
            &pixels,
            &pitch
        );

        uint32_t* pixelData = static_cast<uint32_t*>(pixels);
        
        size_t index = 0;
        for(auto& particle : m_World.GetParticles())
        {
            pixelData[index] = particle.GetColor().MapSDL(SDL_PIXELFORMAT_RGBA32);

            ++index;
        }

        SDL_UnlockTexture(m_Texture);

        SDL_RenderTexture(m_SDLRenderer, m_Texture, nullptr, nullptr);
    }
}