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
        
        bool canFall = world.IsEmpty(below) || world.ParticleAt(below) == ParticleType::Water;
        bool canMoveLeft = world.IsEmpty(downLeft)  || world.ParticleAt(downLeft) == ParticleType::Water;
        bool canMoveRight = world.IsEmpty(downRight) || world.ParticleAt(downRight) == ParticleType::Water;
        
        Vec2 newPosition;

        if(canFall)
        {
            newPosition = below;
        }
        else if(canMoveLeft && canMoveRight)
        {
            int random = std::rand() % 2;

            if(random == 0)
            {
                newPosition = downLeft;
            }
            else
            {
                newPosition = downRight;
            }
        }
        else if(canMoveLeft)
        {
            newPosition = downLeft;
        }
        else if(canMoveRight)
        {
            newPosition = downRight; 
        }
        else
        {
            return false;
        }

        if(world.ParticleAt(newPosition) == ParticleType::Water)
            world.PlaceParticle(new Water, position);
        else
            world.PlaceParticle(new NullParticle, position);
        
        world.PlaceParticle(new Sand, newPosition);
        
        return true;
    }

    bool Rock::Update(World& world, Vec2 position) { return false; }

    bool Water::Update(World& world, Vec2 position)
    {
        Vec2 below = Vec2(position.x, position.y + 1);
        Vec2 left = Vec2(position.x - 1, position.y);
        Vec2 right = Vec2(position.x + 1, position.y);

        bool canFall = world.IsEmpty(below);
        bool canMoveLeft = world.IsEmpty(left);
        bool canMoveRight = world.IsEmpty(right);

        Vec2 newPosition;

        if(canFall)
        {
            newPosition = below;
        }
        else if(canMoveLeft && canMoveRight)
        {
            int random = std::rand() % 2;

            if(random == 0)
            {
                newPosition = left;
            }
            else
            {
                newPosition = right;
            }
        }
        else if(canMoveLeft)
        {
            newPosition = left;
        }
        else if(canMoveRight)
        {
            newPosition = right;   
        }
        else
        {
            return false;
        }

        world.PlaceParticle(new NullParticle, position);
        world.PlaceParticle(new Water, newPosition);

        return true;  
    }
}