#pragma once
#include <SDL_TTF.h>

class AssetManager
{
public:
	AssetManager();
	~AssetManager(); 
	
	static AssetManager* Get();
	TTF_Font* GetFont();
private:
	TTF_Font* font;
	static AssetManager* manager;

};