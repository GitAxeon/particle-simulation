#pragma once

#include "../RGBA.h"
#include <vector>

class Particle
{
public:
    Particle() : m_Color(RGBA(255, 0, 255, 255)) { }
    Particle(RGBA color) : m_Color(color) {}

    RGBA GetColor() { return m_Color; };
    virtual void Update(std::vector<Particle>& particles) { }

private:
    RGBA m_Color;
};

class NullParticle : public Particle
{
public:
    NullParticle() : Particle(RGBA(0, 0, 0, 0)) { }
    void Update(std::vector<Particle>& particles) override { }
};

class Sand : public Particle
{
public: 
    Sand() : Particle(RGBA(194, 178, 128)) { }
    void Update(std::vector<Particle>& particles) override
    {

    }
};

class Rock : public Particle
{
public:
    Rock() : Particle(RGBA(90, 77, 65)) { }
    void Update(std::vector<Particle>& particles) override { }
};