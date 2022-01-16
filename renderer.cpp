// #include <SDL2/SDL.h>
#include "renderer.h"


void Renderer::render()
{
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) exit(0);

        }

    SDL_UpdateWindowSurface(window);
}

Renderer::Renderer()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 960,
        SDL_WINDOW_RESIZABLE);
    SDL_Surface * window_surface = SDL_GetWindowSurface(window);
    pixels = (unsigned int *)window_surface->pixels;
    width = window_surface->w;
    height=window_surface->h;
}

Renderer::~Renderer(){}