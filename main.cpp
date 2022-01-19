#include <stdio.h>

#include <SDL2/SDL.h>

#include "cpu.h"
#include "renderer.h"



int main()
{
    Renderer renderer;
    Cpu cpu ;
    // disable_canonical();
    FILE *read_ptr;
    read_ptr = fopen("test.bin", "rb");
    if(!cpu.load_bin(read_ptr)){
        fprintf(stderr, "Unable to load binary file\n");
        return 1;
    }

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
    // enable_canonical();
    // exit(0);
}
