#include "BasicClock.h"

#include "simulation/ParticleSimulation.h"

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <string>
#include <ctime>

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    
    SDL_Init(SDL_INIT_EVERYTHING);

    ApplicationSpec spec;

    SDL_Window* window = SDL_CreateWindow("Particle simulation", spec.WindowSize.x, spec.WindowSize.y, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsLight();
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

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

        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            ImGui_ImplSDL3_ProcessEvent(&e);

            if(io.WantCaptureMouse || io.WantCaptureKeyboard)
                continue;

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
        
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();
        
        ui.Render(clock.DeltaSeconds());
        ImGui::Render();

        SDL_RenderClear(renderer);

        simulationRenderer.Render();

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);

        if(!simulation.WorldChanged())
            SDL_Delay(1);

    }
    
    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return (EXIT_SUCCESS);
}