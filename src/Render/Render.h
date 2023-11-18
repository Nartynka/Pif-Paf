#pragma once
#include "..\Vec2.h"

struct SDL_Rect;
struct SDL_Texture;
struct SDL_Color;


void RenderInit(); 
void RenderTerminate();

void Render();
void RenderText();

void DrawObject(SDL_Texture* texture, Vec2 size, Vec2 pos);
void DrawObject(SDL_Texture* texture, Vec2 size, Vec2 pos, float angle, Vec2 rotation_point);

void CreateTexture(const char* texture_path, SDL_Texture** out_texture, Vec2& out_size);

void QueueText(const char* new_text, Vec2&& position, SDL_Color color, bool is_bold = false);
void DrawFillRect(SDL_Rect& size, SDL_Color&& color);
void DrawRect(SDL_Rect& size, SDL_Color&& color);
void DrawMole();
void DrawFrog();
void DrawGround();
void DrawCircle(Vec2 pos, int radius);