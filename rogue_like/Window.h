#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Entity.h"

class Window
{
public:
	Window(const char* title, int h, int w);
	SDL_Texture* loadTexture(const char* filePath);
	int getRefreshRate();
	void clear();
	void render(Entity& p_entity);
	void display();
	void clean();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

