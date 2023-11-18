#include <SDL.h>
#include <assert.h>

#include "Render/Render.h"
#include "Cannon/Cannon.h"
#include "Projectile/Projectile.h"
#include <SDL_ttf.h>
#include "AssetManager\AssetManager.h"
#include "Button/Button.h"


void DrawButtons(const char* title, Vec2&& title_pos, int value, Vec2&& value_pos)
{
	static char buffer[20];
	QueueText(title, (Vec2&&)title_pos, { 200, 200, 200 });
	sprintf_s(buffer, "%d", value);
	QueueText(buffer, (Vec2&&)value_pos, { 200, 200, 200 });
}

int main(int argc, char* args[])
{
	float dt = (float)(SDL_GetTicks() / 1000.f);
	float lastTime = 0.f;
	const float DESIRED_DT = 1 / 60.f; // 60 FPS

	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");
	
	result = TTF_Init();
	assert(result != -1 && "SDL_ttf could not initialize!");

	RenderInit();
	AssetManager::Get();

	Cannon* Player = new Cannon();

	Button* rotation_lt_btn = new Button({ 50, 50 }, { 80, 620 }, "<", [Player](float a) { Player->IncreaseRotation(a); }, -5);
	Button* rotation_gt_btn = new Button({ 50, 50 }, { 200, 620 }, ">", [Player](float a) { Player->IncreaseRotation(a); }, 5);

	std::vector<Button*> buttons;
	buttons.push_back(rotation_lt_btn);
	buttons.push_back(rotation_gt_btn);

	

	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		dt = (SDL_GetTicks() - lastTime) / 1000;

		if (dt >= DESIRED_DT)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
					quit = true;
				if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_SPACE)
					Player->Shoot();
				for (Button* btn : buttons)
				{
					btn->HandleInput(event);
				}
			}

			DrawGround();
			DrawFrog();
			DrawMole();

			Player->MoveProjectiles(dt);
		
			DrawButtons("Rotation (in °)", { 70, 580 }, Player->GetRotation(), { 155, 630 });

			Player->Draw();
			Player->DrawProjectiles();

			for (Button* btn : buttons)
			{
				btn->Draw();
			}

			Render();

			lastTime = (float)SDL_GetTicks();

		}
	}

	RenderTerminate();
	SDL_Quit();
	return 0;
}