#pragma once

#include "../RGBA.h"
#include "Math.h"
#include "WorldInfo.h"

namespace ParticleSimulation
{   
    using ElementID = unsigned int;

    namespace Element
    {
        enum : ElementID
        {
            Unknown, Null, Sand, Rock, Water
        };
    };

    class World;
    
    struct Particle
    {
        ElementID ID;
        RGBA Color;
        bool sleep = false;

        Particle() : ID(Element::Null), Color(RGBA(0,0,0,255)) { }
        Particle(ElementID element) : ID(element), Color(RGBA(255,0,255,255)) { }
        Particle(ElementID element, RGBA color) : ID(element), Color(color) { }

        bool Update(World& world, Vec2 position);
    };
}