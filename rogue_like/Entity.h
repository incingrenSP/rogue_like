#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.h"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	Vector2f& getPos()
	{
		return pos;
	}
	SDL_Texture* getTex();
	SDL_Rect getFrame();

private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};

