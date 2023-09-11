#include "BasicClock.h"

#include "simulation/ParticleSimulation.h"

#include <SDL3/SDL.h>

#include <string>
#include <ctime>

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    
    SDL_Init(SDL_INIT_EVERYTHING);
    
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 360;

    SDL_Window* window = SDL_CreateWindow("particle-simulation", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    ParticleSimulation::World simulation(ParticleSimulation::Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ParticleSimulation::Renderer simulationRenderer(simulation, renderer);
    ParticleSimulation::UserInterface ui(simulation);

    bool result = simulation.PlaceParticle(new ParticleSimulation::Water, ParticleSimulation::Vec2(639, 359));
    
    if(result)
    {
        std::cout << "Water placed\n";
    }

    bool painting = false;
    bool erase = false;

    int element = 1;

    BasicClock clock;
    bool open = true;

    while(open)
    {
        clock.Tick();

        SDL_SetWindowTitle(window, std::to_string(1.0/clock.DeltaSeconds()).c_str());

        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    open = false;
                break;
                case SDL_EVENT_KEY_DOWN:
                {
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            open = false;
                        break;
                        case SDLK_p:
                            std::cout << (simulation.ParticleAt(ParticleSimulation::Vec2(0, 0)) == ParticleSimulation::ParticleType::Water ? "Yes" : "No") << std::endl;
                        break;
                        case SDLK_1:
                            element = 1;
                        break;
                        case SDLK_2:
                            element = 2;
                        break;
                        case SDLK_3:
                            element = 3;
                        break;
                    }

                    ui.KeyDown(e);
                } break;
                case SDL_EVENT_KEY_UP:
                    ui.KeyUp(e);
                break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    painting = true;
                    if(e.button.button == SDL_BUTTON_RIGHT)
                        erase = true;
                    
                    ui.MouseDown(e);
                break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    painting = false;

                    if(e.button.button == SDL_BUTTON_RIGHT)
                        erase = false;

                    ui.MouseUp(e);
                break;
            }
        }

        if(painting)
        {
            float mouseXF, mouseYF;
            SDL_GetMouseState(&mouseXF, &mouseYF);
            
            int mouseX = MMath::Clamp<int>(static_cast<int>(mouseXF), 0, simulation.Info.GetWidth() - 1);
            int mouseY = MMath::Clamp<int>(static_cast<int>(mouseYF), 0, simulation.Info.GetHeight() - 1);
            
            ParticleSimulation::Particle* newParticle = nullptr;

            if(!erase)
            {
                switch(element)
                {
                    case 1:
                        newParticle = new ParticleSimulation::Sand;
                    break;
                    case 2: 
                        newParticle = new ParticleSimulation::Rock;
                    break;
                    case 3:
                        newParticle = new ParticleSimulation::Water;
                    break;

                    default:
                        newParticle = new ParticleSimulation::Sand;
                }
            }
            else
                newParticle = new ParticleSimulation::NullParticle;

            bool result = simulation.PlaceParticle(
                newParticle,
                ParticleSimulation::Vec2(mouseX, mouseY)
            );

            // if(result)
            // {
            //     std::cout << "Sand placed at (" << mouseX << ", " << mouseY << ") ";
            //     std::cout << "(" << mouseXF << ", " << mouseYF << ") "; 
            //     std::cout << "index: " << simulation.Info.PositionToIndex(ParticleSimulation::Vec2(mouseX, mouseY)) << std::endl;
            // }
        }

        simulation.Update();
        
        // Render a thing

        if(simulation.WorldChanged())
        {
            SDL_RenderClear(renderer);
            simulationRenderer.Render();
            SDL_RenderPresent(renderer);
        }

        if(!simulation.WorldChanged())
            SDL_Delay(1);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return (EXIT_SUCCESS);
}