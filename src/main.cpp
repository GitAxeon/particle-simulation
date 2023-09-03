#include "BasicClock.h"
#include "simulation/Math.h"

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
    MMath::iVec2 vec1 = MMath::iVec2(1, 0);
    MMath::iVec2 vec2 = MMath::iVec2(3, 5);
    MMath::fVec2 vec3 = vec2.Normalize();
    MMath::dVec2 vec4 = vec2.Normalize();

    std::cout << "Vec1: " << vec1 << std::endl;
    std::cout << "Vec2: " << vec2 << std::endl;
    std::cout << "Plus: " << vec1 + vec2 << std::endl;
    std::cout << "Minus: " << vec1 - vec2 << std::endl;
    std::cout << "Vec2 Scalar mult by -2 : " << vec2 * -2 << std::endl;
    std::cout << "Vec2 length: " << vec2.Length() << std::endl;
    std::cout << "Vec2 dot Vec1: " << vec1.Dot(vec2) << std::endl;
    std::cout << "Vec2 cross vec1: " << vec1.Cross(vec2) << std::endl;
    std::cout << "Angle between Vec1 and Vec2: " << vec1.Angle(vec2) << std::endl;

    SDL_Init(SDL_INIT_EVERYTHING);

    ParticleSimulation ps(640, 360);

    RGBA Empty(0, 0, 0, 0);
    RGBA White(255, 255, 255);
    RGBA Sand(194, 178, 128);

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 360;

    SDL_Window* window = SDL_CreateWindow("particle-simulation", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_PixelFormatEnum pixelFormatEnum = SDL_PIXELFORMAT_RGBA32;
    SDL_PixelFormat* pixelFormat = SDL_CreatePixelFormat(pixelFormatEnum);

    const int SIMULATION_WIDTH = 640;
    const int SIMULATION_HEIGHT = 360;
    const int BYTES_PER_PIXEL = pixelFormat->BytesPerPixel;
    const int PIXEL_COUNT = SIMULATION_WIDTH * SIMULATION_HEIGHT;
    const int PIXEL_DATA_COUNT = SIMULATION_WIDTH * SIMULATION_HEIGHT * BYTES_PER_PIXEL;

    std::vector<RGBA> pixels(PIXEL_COUNT, Empty);

    SDL_Texture* texture = SDL_CreateTexture(renderer, pixelFormatEnum, SDL_TEXTUREACCESS_STREAMING, SIMULATION_WIDTH, SIMULATION_HEIGHT);
    int TEXTURE_PITCH = SIMULATION_WIDTH * BYTES_PER_PIXEL;

    auto UpdateTexture = [&texture, &pixels, &TEXTURE_PITCH, &PIXEL_DATA_COUNT]()
    {
        UpdateTexturePixels(texture, pixels, TEXTURE_PITCH, PIXEL_DATA_COUNT);
    };

    UpdateTexture();

    bool painting = false;
    RGBA currentElement = Sand;

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
                        case SDLK_p:
                        {
                            for(size_t i = 0; i < PIXEL_COUNT; i++)
                            {
                                pixels[i] = Empty;
                            }
                            
                            UpdateTexture();
                        } break;
                        case SDLK_1:
                            currentElement = Sand;
                        break;
                        case SDLK_2:
                            currentElement = Empty;
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
            
            int mouseX = MMath::Clamp<int>(static_cast<int>(mouseXF), 0, SIMULATION_WIDTH - 1);
            int mouseY = MMath::Clamp<int>(static_cast<int>(mouseYF), 0, SIMULATION_HEIGHT - 1);

            if (mouseY >= 0 && mouseY < SIMULATION_HEIGHT - 1)
            {
                pixels[static_cast<size_t>(SIMULATION_WIDTH) * mouseY + mouseX] = currentElement;
                UpdateTexture();
            }
        }

        if(true)//static_cast<int>(clock.DeltaSeconds()) % 2 == 0)
        {
            bool textureNeedsUpdate = false;
            for(size_t i = pixels.size() - 1; i > 0; i--)
            {     
                if(pixels[i] == Sand)
                {
                    int xPosition = i % SIMULATION_WIDTH;
                    int yPosition = i / SIMULATION_WIDTH;

                    if(yPosition < SIMULATION_HEIGHT - 1 && yPosition >= 0)
                    {
                        int newY = yPosition + 1;

                        if(pixels[static_cast<size_t>(SIMULATION_WIDTH) * newY + xPosition] == Empty)
                        {
                            pixels[i] = Empty;
                            pixels[static_cast<size_t>(SIMULATION_WIDTH) * newY + xPosition] = Sand;

                            textureNeedsUpdate = true;
                        }

                        /*
                        else if(true) // Check if both left and right are free then randomly select either one
                        else if(true) // Only left is available, move there
                        else if(true) // only right is available, move there
                        */
                    }

                }
            }
            
            if(textureNeedsUpdate)
                UpdateTexture();
        }
        

        // Render a thing
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyPixelFormat(pixelFormat);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return (EXIT_SUCCESS);
}