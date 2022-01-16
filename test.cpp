// #include <stdio.h>
#include <SDL2/SDL.h>

#include "cpu.h"
#include "renderer.h"

int main()
{
    Renderer renderer;
    Cpu cpu ;
    while (1)
    {
        cpu.cycle();
        renderer.render();
        // // Set every pixel to white.
        // for (int y = 0; y < height/2; ++y)
        // {
        //     for (int x = 0; x < width/2; ++x)
        //     {
        //         pixels[x + y * width] =
        //             SDL_MapRGBA(window_surface->format, 200, 100, 250, 255);
        //     }
        // }

        // SDL_UpdateWindowSurface(window);
    }
}
