#include "Render.h"

#include <SDL.h>
#include <SDL_image.h>
#include <cassert>


SDL_Window* GetWindow()
{
	// Window has to be stored somewhere becouse we have to destroy it at the end
	static SDL_Window* window;

	if (!window)
	{
		window = SDL_CreateWindow("MoleFrog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		assert(window != nullptr && "Window could not be created!");
	}

	return window;
}

SDL_Renderer* GetRenderer()
{
	static SDL_Renderer* renderer;

	if (!renderer)
	{
		renderer = SDL_CreateRenderer(GetWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		assert(renderer != nullptr && "Renderer could not be created!");
	}

	return renderer;
}

void RenderInit()
{
	GetWindow();
	GetRenderer();
}

void RenderTerminate()
{
	SDL_DestroyWindow(GetWindow());
}

void Render()
{
	SDL_SetRenderDrawColor(GetRenderer(), 0, 0, 0, 255);
	SDL_RenderPresent(GetRenderer());
}

void DrawRect(SDL_Rect& size, SDL_Color&& color)
{
	SDL_SetRenderDrawColor(GetRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(GetRenderer(), &size);
}

void DrawFrog()
{
	SDL_Rect frogHead = { SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 50, 100, 50 };
	DrawRect(frogHead, { 100, 255, 50, 255 });

	SDL_Rect frog = { SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2, 200, 100 };
	DrawRect(frog, { 100, 255, 50, 255 });
}

void DrawMole()
{
	SDL_Rect moleHead = { SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 50, 100, 50 };	
	DrawRect(moleHead, { 100, 100, 100, 255 });

	SDL_Rect mole = { SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2, 200, 100 };
	DrawRect(mole, { 100, 100, 100, 255 });
}
