#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

class Application
{
public:
    Application();
    ~Application();
    void updateScreen();
    SDL_Event m_window_event;
    SDL_Window* m_window = NULL;
    SDL_Surface* m_window_surface = NULL;
    SDL_Renderer* m_renderer = NULL;
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;
};