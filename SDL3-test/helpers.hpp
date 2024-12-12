#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>

SDL_Surface* loadSurface(std::string path, SDL_Surface* window_surface);

class LTexture
{
public:
    //Initializes texture variables
    LTexture();

    //Cleans up texture variables
    ~LTexture();

    //Loads texture from disk
    bool loadFromFile(std::string path, SDL_Renderer* renderer);

    //Cleans up texture
    void destroy();

    //Draws texture
    void render(float x, float y, SDL_Renderer* renderer);

    //Gets texture dimensions
    int getWidth();
    int getHeight();

private:
    //Contains texture data
    SDL_Texture* mTexture = nullptr;

    //Texture dimensions
    int mWidth;
    int mHeight;
};