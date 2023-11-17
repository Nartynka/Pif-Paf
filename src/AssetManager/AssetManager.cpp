#include "AssetManager.h"
#include <assert.h>


AssetManager* AssetManager::manager = nullptr;

AssetManager* AssetManager::Get()
{
	if (!manager)
	{
		manager = new AssetManager();
	}

	return manager;
}

AssetManager::AssetManager()
{
	font = TTF_OpenFont("res/fonts/consola.ttf", 24);
	assert(font != nullptr && "Font could not be created!");

	bold_font = TTF_OpenFont("res/fonts/consola-bold.ttf", 24);
	assert(font != nullptr && "Bold Font could not be created!");
}

AssetManager::~AssetManager()
{
	TTF_CloseFont(font);
	delete manager;
}

TTF_Font* AssetManager::GetFont()
{
	return font;
}

TTF_Font* AssetManager::GetBoldFont()
{
	return bold_font;
}