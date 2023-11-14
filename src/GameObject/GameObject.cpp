#include "GameObject.h"

#include "../Globals.h"
#include "../Render/Render.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{

}

void GameObject::Draw()
{
	DrawObject(texture, size, position);
}
