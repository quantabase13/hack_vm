#pragma once
#include <SDL2/SDL.h>

class Renderer
{
    public:
        void render();
        Renderer();
    ~Renderer();
    private:
        SDL_Window * window;
        int width;
        int height;
        unsigned int *pixels;
};