#include <iostream>
#include <SDL3/SDL.h>

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Meh" << std::endl;
    }

    std::cout << "Runnin\n";
    return (EXIT_SUCCESS);
}