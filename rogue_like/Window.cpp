#include "Window.h"

Window::Window(const char* title, int h, int w)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window could not be created. Error: " << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* Window::loadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL) {
		std::cout << "Texture could not be created. Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

int Window::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

void Window::clear()
{
	SDL_RenderClear(renderer);
}

void Window::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getFrame().x;
	src.y = p_entity.getFrame().y;
	src.w = p_entity.getFrame().w;
	src.h = p_entity.getFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getFrame().w * 4;
	dst.h = p_entity.getFrame().h * 4;
	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void Window::display()
{
	SDL_RenderPresent(renderer);
}

void Window::clean()
{
	SDL_DestroyWindow(window);
	std::cout << "Session ended.";
}