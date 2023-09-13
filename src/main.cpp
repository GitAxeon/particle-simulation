#include "BasicClock.h"

#include "simulation/ParticleSimulation.h"

#include <SDL3/SDL.h>

#include <string>
#include <ctime>

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    
    SDL_Init(SDL_INIT_EVERYTHING);

    ApplicationSpec spec;

    SDL_Window* window = SDL_CreateWindow("particle-simulation", spec.WindowSize.x, spec.WindowSize.y, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    ParticleSimulation::World simulation(spec.WindowSize);
    ParticleSimulation::Renderer simulationRenderer(simulation, renderer);
    ParticleSimulation::UserInterface ui(simulation, spec);

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
                case SDL_EVENT_MOUSE_WHEEL:
                    ui.MouseWheel(e);
                break;
            }
        }

        ui.HandleInput();
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