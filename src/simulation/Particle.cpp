#include "Particle.h"
#include "World.h"

namespace ParticleSimulation
{
    bool Particle::Update(World& world, Vec2 position) { return false; }

    bool NullParticle::Update(World& world, Vec2 position) { return false; }

    bool Sand::Update(World& world, Vec2 position)
    {
        Vec2 below = Vec2(position.x, position.y + 1);
        Vec2 downLeft = Vec2(position.x - 1, position.y + 1);
        Vec2 downRight = Vec2(position.x + 1, position.y + 1);

        bool canFall = world.Info.IsValidPosition(below) && world.IsEmpty(below);
        bool canMoveLeft = world.Info.IsValidPosition(downLeft) && world.IsEmpty(downLeft);
        bool canMoveRight = world.Info.IsValidPosition(downRight) && world.IsEmpty(downRight);
        

        if(canFall)
        {
            world.PlaceParticle(new NullParticle, position);
            world.PlaceParticle(new Sand, below);
        }
        else if(canMoveLeft && canMoveRight)
        {
            int random = std::rand() % 2;

            if(random == 0)
            {
                world.PlaceParticle(new NullParticle, position);
                world.PlaceParticle(new Sand, downLeft);
            }
            else
            {
                world.PlaceParticle(new NullParticle, position);
                world.PlaceParticle(new Sand, downRight);
            }
        }
        else if(canMoveLeft)
        {
            world.PlaceParticle(new NullParticle, position);
            world.PlaceParticle(new Sand, downLeft);
        }
        else if(canMoveRight)
        {
            world.PlaceParticle(new NullParticle, position);
            world.PlaceParticle(new Sand, downRight);     
        }
        else
        {
            return false;
        }

        return true;
    }

    bool Rock::Update(World& world, Vec2 position) { return false; }
}