#pragma once

#include "World.h"

#include <SDL3/SDL.h>

namespace ParticleSimulation
{
    enum class BrushType { Pixel, Circular, Rectangular };
    enum class Tool { Brush, Eraser };

    class UserInterface
    {
    public:
        UserInterface(World& world) : m_World(world) { };

        void KeyDown(SDL_Event& event);
        void KeyUp(SDL_Event& event);
        void MouseDown(SDL_Event& event);
        void MouseUp(SDL_Event& event);

    private:
        World& m_World;
    };
}