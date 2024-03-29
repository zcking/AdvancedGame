#include <iostream>

#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice(Uint32 width, Uint32 height) : SCREEN_WIDTH(width),
SCREEN_HEIGHT(height)
{
	screen = NULL;
}

GraphicsDevice::~GraphicsDevice()
{
	if (!Shutdown())
	{
		printf("SDL could not shut down! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
}

bool GraphicsDevice::Initialize(bool fullScreen)
{
	// Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialize SDL_image subsystems
	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError());
		return false;
	}

	if (!fullScreen)
	{
		screen = SDL_CreateWindow(
			"The Legend of Zelda",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	}
	else
	{
		screen = SDL_CreateWindow(
			"The Legend of Zelda",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_FULLSCREEN);
	}

	// Construct the renderer
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Set the background color (default)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	return true;
}

bool GraphicsDevice::Shutdown()
{
	// Free the window
	SDL_DestroyWindow(screen);
	screen = NULL;

	// Free the renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	// Quit subsystems
	IMG_Quit();
	SDL_Quit();
	return true;
}

void GraphicsDevice::Begin()
{
	// Render the desert-color background over everything
	SDL_SetRenderDrawColor(renderer, 255, 219, 173, 255);
	SDL_RenderClear(renderer);
}

void GraphicsDevice::Present()
{
	// Update rendering
	SDL_RenderPresent(renderer);
}

// Getter for renderer member
SDL_Renderer* GraphicsDevice::getRenderer()
{
	return renderer;
}
