#pragma once
#include <SDL_TTF.h>

class AssetManager
{
public:
	AssetManager();
	~AssetManager(); 
	
	static AssetManager* Get();
	TTF_Font* GetFont();
	TTF_Font* GetBoldFont();
private:
	TTF_Font* font;
	TTF_Font* bold_font;
	static AssetManager* manager;
};