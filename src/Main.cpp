#include <SDL.h>
#include <assert.h>

#include "Render/Render.h"
#include "Cannon/Cannon.h"
#include "Projectile/Projectile.h"
#include <SDL_ttf.h>
#include "AssetManager\AssetManager.h"
#include "Button/Button.h"

void DrawControls(const char* title, Vec2&& title_pos, int value, Vec2&& value_pos, char* buffer)
{
	QueueText(title, (Vec2&&)title_pos, { 230, 230, 230 });
	sprintf_s(buffer, 4, "%d", value);
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

	Button* rotation_lt_btn = new Button({ 40, 40 }, { 80, 620 }, "<", [&Player](float value) { Player->IncreaseRotation(value); }, -5);
	Button* rotation_gt_btn = new Button({ 40, 40 }, { 180, 620 }, ">", [&Player](float value) { Player->IncreaseRotation(value); }, 5);

	Button* velocity_lt_btn = new Button({ 40, 40 }, { 80 + 300, 620 }, "<", [&Player](float value) { Player->IncreaseVelocity(value); }, -5);
	Button* velocity_gt_btn = new Button({ 40, 40 }, { 180 + 300, 620 }, ">", [&Player](float value) { Player->IncreaseVelocity(value); }, 5);

	Button* gravity_lt_btn = new Button({ 40, 40 }, { 80 + 300 * 2, 620 }, "<", [&Player](float value) { Player->IncreaseGravity(value); }, -5);
	Button* gravity_gt_btn = new Button({ 40, 40 }, { 180 + 300 * 2, 620 }, ">", [&Player](float value) { Player->IncreaseGravity(value); }, 5);

	Button* air_drag_lt_btn = new Button({ 40, 40 }, { 80 + 300 * 3, 620 }, "<", [&Player](float value) { Player->IncreaseAirDrag(value); }, -1);
	Button* air_drag_gt_btn = new Button({ 40, 40 }, { 180 + 300 * 3, 620 }, ">", [&Player](float value) { Player->IncreaseAirDrag(value); }, 1);

	std::vector<Button*> buttons;
	buttons.push_back(rotation_lt_btn);
	buttons.push_back(rotation_gt_btn);

	buttons.push_back(velocity_lt_btn);
	buttons.push_back(velocity_gt_btn);

	buttons.push_back(gravity_lt_btn);
	buttons.push_back(gravity_gt_btn);

	buttons.push_back(air_drag_lt_btn);
	buttons.push_back(air_drag_gt_btn);

	char rotation_buffer[4];
	char velocity_buffer[4];
	char gravity_buffer[4];
	char air_drag_buffer[4];


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
			Player->Draw();
			Player->DrawProjectiles();

			DrawControls("Rotation", { 98, 585 }, Player->GetRotation(), { 137, 629 }, rotation_buffer);
			DrawControls("Initial velocity", { 345, 585 }, Player->GetVelocity(), { 137 + 300, 629 }, velocity_buffer);
			DrawControls("Gravity", { 98 + 300 * 2, 585 }, Player->GetGravity(), { 137 + 300 * 2, 629 }, gravity_buffer);
			DrawControls("Air Drag", { 98 + 300 * 3, 585 }, Player->GetAirDrag(), { 137 + 300 * 3, 629 }, air_drag_buffer);

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