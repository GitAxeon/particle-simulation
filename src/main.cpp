#include "BasicClock.h"

#include "simulation/ParticleSimulation.h"

#include <SDL3/SDL.h>

void UpdateTexturePixels(SDL_Texture* texture, const std::vector<RGBA>& newPixels, int pitch, int dataCount)
{
    void* writeOnlyPixels = nullptr;
    SDL_LockTexture(texture, nullptr, &writeOnlyPixels, &pitch);
    std::memcpy(writeOnlyPixels, newPixels.data(), dataCount);
    SDL_UnlockTexture(texture);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // RGBA Empty(0, 0, 0, 0);
    // RGBA White(255, 255, 255);
    // RGBA Sand(194, 178, 128);

    const int WINDOW_WIDTH = 320;
    const int WINDOW_HEIGHT = 180;

    SDL_Window* window = SDL_CreateWindow("particle-simulation", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // SDL_PixelFormatEnum pixelFormatEnum = SDL_PIXELFORMAT_RGBA32;
    // SDL_PixelFormat* pixelFormat = SDL_CreatePixelFormat(pixelFormatEnum);

    // const int SIMULATION_WIDTH = 640;
    // const int SIMULATION_HEIGHT = 360;
    // const int BYTES_PER_PIXEL = pixelFormat->BytesPerPixel;
    // const int PIXEL_COUNT = SIMULATION_WIDTH * SIMULATION_HEIGHT;
    // const int PIXEL_DATA_COUNT = SIMULATION_WIDTH * SIMULATION_HEIGHT * BYTES_PER_PIXEL;

    // std::vector<RGBA> pixels(PIXEL_COUNT, Empty);

    // SDL_Texture* texture = SDL_CreateTexture(renderer, pixelFormatEnum, SDL_TEXTUREACCESS_STREAMING, SIMULATION_WIDTH, SIMULATION_HEIGHT);
    // int TEXTURE_PITCH = SIMULATION_WIDTH * BYTES_PER_PIXEL;

    // auto UpdateTexture = [&texture, &pixels, &TEXTURE_PITCH, &PIXEL_DATA_COUNT]()
    // {
    //     //UpdateTexturePixels(texture, pixels, TEXTURE_PITCH, PIXEL_DATA_COUNT);
    // };

    // UpdateTexture();

    // RGBA currentElement = Sand;

    ParticleSimulation::World simulation(ParticleSimulation::Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ParticleSimulation::Renderer simulationRenderer(simulation, renderer);
    ParticleSimulation::UserInterface ui(simulation);

    bool painting = false;

    BasicClock clock;
    bool open = true;

    while(open)
    {
        clock.Tick();

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
                break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    painting = false;
                break;
            }
        }

        if(painting)
        {
            float mouseXF, mouseYF;
            SDL_GetMouseState(&mouseXF, &mouseYF);
            
            int mouseX = MMath::Clamp<int>(static_cast<int>(mouseXF), 0, simulation.Info.GetWidth() - 1);
            int mouseY = MMath::Clamp<int>(static_cast<int>(mouseYF), 0, simulation.Info.GetHeight() - 1);

            // if (mouseY >= 0 && mouseY < SIMULATION_HEIGHT - 1)
            // {
            //     pixels[static_cast<size_t>(SIMULATION_WIDTH) * mouseY + mouseX] = currentElement;
            //     UpdateTexture();
            // }

            simulation.PlaceParticle(
                new ParticleSimulation::Sand,
                ParticleSimulation::Vec2(mouseX, mouseY)
            );

            // std::cout << "Sand placed at (" << mouseX << ", " << mouseY << ") ";
            // std::cout << "(" << mouseXF << ", " << mouseYF << ") "; 
            // std::cout << "index: " << simulation.Info.PositionToIndex(ParticleSimulation::Vec2(mouseX, mouseY)) << std::endl;
        }

        // if(true)//static_cast<int>(clock.DeltaSeconds()) % 2 == 0)
        // {
        //     bool textureNeedsUpdate = false;
        //     for(size_t i = pixels.size() - 1; i > 0; i--)
        //     {     
        //         if(pixels[i] == Sand)
        //         {
        //             int xPosition = i % SIMULATION_WIDTH;
        //             int yPosition = i / SIMULATION_WIDTH;

        //             if(yPosition < SIMULATION_HEIGHT - 1 && yPosition >= 0)
        //             {
        //                 int newY = yPosition + 1;

        //                 if(pixels[static_cast<size_t>(SIMULATION_WIDTH) * newY + xPosition] == Empty)
        //                 {
        //                     pixels[i] = Empty;
        //                     pixels[static_cast<size_t>(SIMULATION_WIDTH) * newY + xPosition] = Sand;

        //                     textureNeedsUpdate = true;
        //                 }

        //                 /*
        //                 else if(true) // Check if both left and right are free then randomly select either one
        //                 else if(true) // Only left is available, move there
        //                 else if(true) // only right is available, move there
        //                 */
        //             }

        //         }
        //     }
            
        //     if(textureNeedsUpdate)
        //         UpdateTexture();
        // }
        

        // Render a thing
        SDL_RenderClear(renderer);
        // SDL_RenderTexture(renderer, texture, nullptr, nullptr);

        ui.HandleInput();
        simulation.Update();
        simulationRenderer.Render();

        SDL_RenderPresent(renderer);

    }

    // SDL_DestroyPixelFormat(pixelFormat);
    // SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return (EXIT_SUCCESS);
}