#include "Particle.h"
#include "World.h"

namespace ParticleSimulation
{
    bool Particle::Update(World& world, Vec2 position) { return false; }

    bool NullParticle::Update(World& world, Vec2 position) { return false; }

    bool Sand::Update(World& world, Vec2 position)
    {
        Vec2 below = Vec2(position.x, position.y + 1);
        bool canFall = world.Info.IsValidPosition(below);

        if(!canFall)
            return false;

        bool isEmpty = dynamic_cast<NullParticle*>(world.GetParticles()[world.Info.PositionToIndex(below)]);

        if(!isEmpty)
            return false;

        world.PlaceParticle(new NullParticle, position);
        world.PlaceParticle(new Sand, below);

        return true;
    }

    bool Rock::Update(World& world, Vec2 position) { return false; }
}