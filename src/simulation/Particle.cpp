#include "Particle.h"
#include "World.h"

namespace ParticleSimulation
{
    void Particle::Update(World& world, Vec2 position) { }

    void NullParticle::Update(World& world, Vec2 position) { }

    void Sand::Update(World& world, Vec2 position)
    {
        Vec2 below = Vec2(position.x, position.y + 1);
        bool canFall = world.Info.IsValidPosition(below);

        bool isEmpty = dynamic_cast<NullParticle*>(world.GetParticles()[world.Info.PositionToIndex(below)]);

        if(canFall && isEmpty)
        {
            world.PlaceParticle(new Sand, below);
            world.PlaceParticle(new NullParticle, position);
        }
    }

    void Rock::Update(World& world, Vec2 position) { }
}