#include "BasicClock.h"

#include "simulation/ParticleSimulation.h"

#include <SDL3/SDL.h>

#include <string>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 360;

    SDL_Window* window = SDL_CreateWindow("particle-simulation", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    ParticleSimulation::World simulation(ParticleSimulation::Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ParticleSimulation::Renderer simulationRenderer(simulation, renderer);
    ParticleSimulation::UserInterface ui(simulation);

    bool painting = false;
    bool erase = false;

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
                    }
                } break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    painting = true;
                    if(e.button.button == SDL_BUTTON_RIGHT)
                        erase = true;
                break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    painting = false;

                    if(e.button.button == SDL_BUTTON_RIGHT)
                        erase = false;
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

            if(erase)
                newParticle = new ParticleSimulation::NullParticle;
            else
                newParticle = new ParticleSimulation::Sand;

            simulation.PlaceParticle(
                newParticle,
                ParticleSimulation::Vec2(mouseX, mouseY)
            );

            // std::cout << "Sand placed at (" << mouseX << ", " << mouseY << ") ";
            // std::cout << "(" << mouseXF << ", " << mouseYF << ") "; 
            // std::cout << "index: " << simulation.Info.PositionToIndex(ParticleSimulation::Vec2(mouseX, mouseY)) << std::endl;
        }

        // Render a thing
        SDL_RenderClear(renderer);

        ui.HandleInput();
        simulation.Update();
        simulationRenderer.Render();

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return (EXIT_SUCCESS);
}