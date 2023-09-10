#pragma once

#include "../RGBA.h"
#include "WorldInfo.h"

namespace ParticleSimulation
{
    class World;

    enum class ParticleType
    {
        Unknown,
        NullParticle,
        Sand,
        Rock
    };
    
    class Particle
    {
    public:
        Particle() : m_Color(RGBA(255, 0, 255, 255)), m_Type(ParticleType::Unknown) { }
        Particle(RGBA color, ParticleType type) : m_Color(color), m_Type(type) {}

        RGBA GetColor() const { return m_Color; };
        void SetColor(const RGBA& color) { m_Color = color; }
        
        virtual bool Update(World& world, Vec2 position);
        ParticleType GetType() const { return m_Type; }

    private:
        RGBA m_Color;
        ParticleType m_Type;
    };

    class NullParticle : public Particle
    {
    public:
        NullParticle() : Particle(RGBA(0, 0, 0, 0), ParticleType::NullParticle) { }
        bool Update(World& world, Vec2 position) override;
    };

    class Sand : public Particle
    {
    public: 
        Sand() : Particle(RGBA(194, 178, 128), ParticleType::Sand) { }

        bool Update(World& world, Vec2 position) override;
    };

    class Rock : public Particle
    {
    public:
        Rock() : Particle(RGBA(90, 77, 65), ParticleType::Rock) { }
        bool Update(World& world, Vec2 position) override;
    };
}