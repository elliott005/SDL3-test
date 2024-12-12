#include "helpers.hpp"


SDL_Surface* loadSurface(std::string path, SDL_Surface* window_surface)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		//printf("%i", window_surface->format); //370546692; 0x16161804
		optimizedSurface = SDL_ConvertSurface(loadedSurface, SDL_PIXELFORMAT_ARGB8888);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		/*int success = SDL_SetSurfaceBlendMode(optimizedSurface, SDL_BLENDMODE_BLEND);
		if (success != 0) {
			printf("SDL_SetSurfaceBlendMode failed with exit code: %i! SDL Error: %s\n", success, SDL_GetError());
		}*/

		//Get rid of old loaded surface
		SDL_DestroySurface(loadedSurface);
	}

	return optimizedSurface;
}

LTexture::LTexture() 
{
	//Initialize texture variables
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Clean up texture
	destroy();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	//Clean up texture if it already exists
	destroy();

	//Load surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Create texture from surface
		mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (mTexture == nullptr)
		{
			SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Clean up loaded surface
		SDL_DestroySurface(loadedSurface);
	}

	//Return success if texture loaded
	return mTexture != nullptr;
}

void LTexture::destroy()
{
	//Clean up texture
	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

void LTexture::render(float x, float y, SDL_Renderer* renderer)
{
	//Set texture position
	SDL_FRect dstRect = { x, y, static_cast<float>(mWidth), static_cast<float>(mHeight) };

	//Render texture
	SDL_RenderTexture(renderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}