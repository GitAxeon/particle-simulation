#pragma once

#include "ParticleBehaviour.h"
#include "World.h"

namespace ParticleSimulation
{
    class SandBehaviour : public ParticleBehaviour
    {
        bool Update(World& world, ParticleData& particle, Vec2 position)
        {
            const ParticleDatabase& pdb = world.GetParticleDatabase();
            ParticleData nullparticle = pdb.Get(0);

            Vec2 below = Vec2(position.x, position.y + 1);
            bool liquidBelow = world.ParticleAt(below).MatterState == StateOfMatter::Liquid;
            bool canFall = world.IsEmpty(below) || liquidBelow;

            if(canFall)
            {
                world.SwapParticle(position, below);

                return true;
            }

            Vec2 left(position.x - 1, position.y);
            Vec2 downLeft = Vec2(position.x - 1, position.y + 1);

            Vec2 right(position.x + 1, position.y);
            Vec2 downRight = Vec2(position.x + 1, position.y + 1);

            bool canMoveLeft = world.IsEmpty(left) && world.IsEmpty(downLeft);
            bool canMoveRight = world.IsEmpty(right) && world.IsEmpty(downRight);

            if(canMoveLeft && canMoveRight)
            {
                int random = std::rand() % 2;

                world.SwapParticle(position, random ? downLeft : downRight);
                // if(random == 0)
                // {
                //     world.SwapParticle(position, downLeft);
                // }
                // else
                // {
                //     world.SwapParticle(position, downRight);
                // }
            }
            else if(canMoveLeft)
            {
                world.SwapParticle(position, downLeft);
            }
            else if(canMoveRight)
            {
                world.SwapParticle(position, downRight);
            }
            else 
            {
                return false;
            }

            return true;
        }
    };
    
    class WaterBehaviour : public ParticleBehaviour
    {
        bool Update(World& world, ParticleData& particle, Vec2 position)
        {
            Vec2 below = Vec2(position.x, position.y + 1);
            bool canFall = world.IsEmpty(below);

            Vec2 newPosition;

            if(canFall)
            {
                world.SwapParticle(position, below);

                return true;
            }
            
            Vec2 left(position.x - 1, position.y);
            Vec2 right(position.x + 1, position.y);
            
            bool liquidOnLeft = world.ParticleAt(left).MatterState == StateOfMatter::Liquid;
            bool liquidOnRight = world.ParticleAt(right).MatterState == StateOfMatter::Liquid;

            bool canMoveLeft = world.IsEmpty(left) || liquidOnLeft;
            bool canMoveRight = world.IsEmpty(right) || liquidOnRight;

            if(canMoveLeft && canMoveRight)
            {
                int random = std::rand() % 2;

                world.SwapParticle(position, random ? left : right);

                // if(random == 0)
                // {
                //     world.SwapParticle(position, left);
                // }
                // else
                // {
                //     world.SwapParticle(position, right);
                // }
            }
            else if(canMoveLeft)
            {
                world.SwapParticle(position, left);
            }
            else if(canMoveRight)
            {
                world.SwapParticle(position, right);
            }
            else 
            {
                return false;
            }

            return true;
        }
    };
}