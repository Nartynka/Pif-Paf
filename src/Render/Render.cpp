#include "Render.h"

#include "..\AssetManager\AssetManager.h"
#include "..\Globals.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cassert>
#include <vector>
#include "..\Text\Text.h"

SDL_Window* GetWindow()
{
	// Window has to be stored somewhere because we have to destroy it at the end
	static SDL_Window* window;

	if (!window)
	{
		window = SDL_CreateWindow("Pif-Paf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
	RenderText();
	SDL_SetRenderDrawColor(GetRenderer(), 255, 255, 255, 255);
	SDL_RenderPresent(GetRenderer());
	SDL_RenderClear(GetRenderer());
}

void CreateTexture(const char* texture_path, SDL_Texture** out_texture, Vec2& out_size)
{
	assert(texture_path != nullptr && "Texture path was not specified!");
	SDL_Surface* loaded_surface = IMG_Load(texture_path);
	assert(loaded_surface != nullptr && "Unable to load image");
	*out_texture = SDL_CreateTextureFromSurface(GetRenderer(), loaded_surface);
	assert(out_texture != nullptr && "Unable to create texture from surface!");
	out_size = { (float)loaded_surface->w, (float)loaded_surface->h };
	SDL_FreeSurface(loaded_surface);
}

void DrawObject(SDL_Texture* texture, Vec2 size, Vec2 pos)
{
	SDL_Rect dsrect = { pos.x, pos.y, size.x, size.y };
	assert(texture != nullptr && "Could not draw object, texture invalid!");
	SDL_RenderCopy(GetRenderer(), texture, NULL, &dsrect);
}

void DrawObject(SDL_Texture* texture, Vec2 size, Vec2 pos, float angle, Vec2 rotation_point)
{
	SDL_Rect dsrect = { pos.x, pos.y, size.x, size.y };
	assert(texture != nullptr && "Could not draw object, texture invalid!");
	SDL_Point* center = new SDL_Point({ (int)rotation_point.x, (int)rotation_point.y });
	SDL_SetRenderDrawColor(GetRenderer(), 255, 0, 0, 255);

	SDL_RenderDrawPoint(GetRenderer(), pos.x + rotation_point.x, pos.y + rotation_point.y);
	SDL_RenderDrawPoint(GetRenderer(), pos.x + rotation_point.x+1, pos.y + rotation_point.y + 1);
	SDL_RenderDrawPoint(GetRenderer(), pos.x + rotation_point.x + 1, pos.y + rotation_point.y);
	SDL_RenderDrawPoint(GetRenderer(), pos.x + rotation_point.x, pos.y + rotation_point.y + 1);
	SDL_RenderDrawPoint(GetRenderer(), pos.x + rotation_point.x - 1, pos.y + rotation_point.y-1);
	SDL_RenderDrawPoint(GetRenderer(), pos.x + rotation_point.x - 1, pos.y + rotation_point.y);
	SDL_RenderDrawPoint(GetRenderer(), pos.x + rotation_point.x, pos.y + rotation_point.y-1);

	SDL_RenderCopyEx(GetRenderer(), texture, NULL, &dsrect, (double)angle, center, SDL_FLIP_NONE);
}

void DrawFillRect(SDL_Rect& size, SDL_Color&& color)
{
	SDL_SetRenderDrawColor(GetRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(GetRenderer(), &size);
}

void DrawRect(SDL_Rect& size, SDL_Color&& color)
{
	SDL_SetRenderDrawColor(GetRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(GetRenderer(), &size);

	//SDL_RenderDrawRect(GetRenderer(), {size.x, size.y, size.w, size.h});
}



void DrawGround()
{
	SDL_Rect ground = { 0, GROUND_LEVEL, SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_LEVEL };
	DrawFillRect(ground, { 100, 100, 100, 255 });
}



void DrawCircle(Vec2 pos, int radius)
{
	SDL_Renderer* renderer = GetRenderer();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, pos.x + dx, pos.y + dy);
			}
		}
	}
}

std::vector<Text*> queued_text;

void QueueText(const char* new_text, Vec2&& position, SDL_Color color, bool is_bold)
{	
	Text* text_struct = new Text({ new_text, position, color, is_bold});
	queued_text.push_back(text_struct);
}

void RenderText()
{
	TTF_Font* font = AssetManager::Get()->GetFont();
	assert(font != nullptr && "Unable to get font from asset manager");
	TTF_Font* bold_font = AssetManager::Get()->GetBoldFont();
	assert(bold_font != nullptr && "Unable to get bold font from asset manager");

	SDL_Renderer* renderer = GetRenderer();

	for (Text* text_struct : queued_text)
	{
		SDL_Surface* text_surface = TTF_RenderText_Solid(text_struct->is_bold ? bold_font : font, text_struct->text, text_struct->color);
		assert(text_surface != nullptr && "Unable to create text surface!");
		SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		assert(text_texture != NULL && "Unable to create texture from rendered text!");

		SDL_Rect text_dsrect = { text_struct->position.x, text_struct->position.y, text_surface->w, text_surface->h };
		SDL_RenderCopy(renderer, text_texture, NULL, &text_dsrect);

		SDL_FreeSurface(text_surface);
		SDL_DestroyTexture(text_texture);
		delete text_struct;
	}

	queued_text.clear();
}