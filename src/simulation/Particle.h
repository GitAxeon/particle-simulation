#pragma once

#include "../RGBA.h"
#include "WorldInfo.h"

namespace ParticleSimulation
{
    class World;
    
    class Particle
    {
    public:
        Particle() : m_Color(RGBA(255, 0, 255, 255)) { }
        Particle(RGBA color) : m_Color(color) {}

        RGBA GetColor() { return m_Color; };
        void SetColor(const RGBA& color) { m_Color = color; }
        
        virtual bool Update(World& world, Vec2 position);

    private:
        RGBA m_Color;
    };

    class NullParticle : public Particle
    {
    public:
        NullParticle() : Particle(RGBA(0, 0, 0, 0)) { }
        bool Update(World& world, Vec2 position) override;
    };

    class Sand : public Particle
    {
    public: 
        Sand() : Particle(RGBA(194, 178, 128)) { }

        bool Update(World& world, Vec2 position) override;
    };

    class Rock : public Particle
    {
    public:
        Rock() : Particle(RGBA(90, 77, 65)) { }
        bool Update(World& world, Vec2 position) override;
    };
}