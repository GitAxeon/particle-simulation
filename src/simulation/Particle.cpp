#include "Particle.h"
#include "World.h"

namespace ParticleSimulation
{
    bool Particle::Update(World& world, Vec2 position)
    {
        switch(ID)
        {
            case Element::Sand:
            {
                Vec2 below = Vec2(position.x, position.y + 1);
                bool waterBelow = world.ParticleAt(below) == Element::Water;
                bool canFall = world.IsEmpty(below) || waterBelow;

                Vec2 newPosition;

                if(canFall)
                {
                    if(waterBelow)
                        world.PlaceParticle(Element::Water, position);
                    else
                        world.PlaceParticle(Element::Null, position);

                    world.PlaceParticle(Element::Sand, below);

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

                    if(random == 0)
                    {
                        world.PlaceParticle(Element::Null, position);
                        world.PlaceParticle(Element::Sand, downLeft);
                    }
                    else
                    {
                        world.PlaceParticle(Element::Null, position);
                        world.PlaceParticle(Element::Sand, downRight);
                    }
                }
                else if(canMoveLeft)
                {
                    world.PlaceParticle(Element::Null, position);
                    world.PlaceParticle(Element::Sand, downLeft);
                }
                else if(canMoveRight)
                {
                    world.PlaceParticle(Element::Null, position);
                    world.PlaceParticle(Element::Sand, downRight);
                }
                else 
                {
                    return false;
                }

                return true;
            } break;

            case Element::Water:
            {
                Vec2 below = Vec2(position.x, position.y + 1);
                bool canFall = world.IsEmpty(below);

                Vec2 newPosition;

                if(canFall)
                {
                    world.PlaceParticle(Element::Null, position);
                    world.PlaceParticle(Element::Water, below);

                    return true;
                }
                
                Vec2 left(position.x - 1, position.y);
                Vec2 right(position.x + 1, position.y);
                bool waterOnLeft = world.ParticleAt(left) == Element::Water;
                bool waterOnRight = world.ParticleAt(right) == Element::Water;

                bool canMoveLeft = world.IsEmpty(left) || waterOnLeft;
                bool canMoveRight = world.IsEmpty(right) || waterOnRight;

                if(canMoveLeft && canMoveRight)
                {
                    int random = std::rand() % 2;

                    if(random == 0)
                    {
                        if(waterOnLeft)
                            world.PlaceParticle(Element::Water, position);
                        else
                            world.PlaceParticle(Element::Null, position);
                        
                        world.PlaceParticle(Element::Water, left);
                    }
                    else
                    {
                        if(waterOnRight)
                        {
                            world.SwapParticle(position, right);
                        }
                        else
                        {
                            world.PlaceParticle(Element::Null, position);
                            world.PlaceParticle(Element::Water, right);
                        }
                    }
                }
                else if(canMoveLeft)
                {
                    if(waterOnLeft)
                    {
                        world.SwapParticle(position, left);
                    }
                    else
                    {
                        world.PlaceParticle(Element::Null, position);
                        world.PlaceParticle(Element::Water, left);
                    }
                }
                else if(canMoveRight)
                {
                    if(waterOnRight)
                        world.PlaceParticle(Element::Water, position);
                    else
                        world.PlaceParticle(Element::Null, position);

                    world.PlaceParticle(Element::Water, right);
                }
                else 
                {
                    return false;
                }

                return true;
            } break;
        }

        return false;
    }
}