#include "Window.h"
#include "Entity.h"
#include "Utils.h"
#include "Math.h"

#include <vector>

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
		std::cout << "SDL2 initialisation failed. Error: " << SDL_GetError() << std::endl;
	}
	
	Window window("Rogue", 1280, 720);

	SDL_Texture* p_idleTex = window.loadTexture("res/p_idle.png");

	std::vector<Entity> entity = { Entity(Vector2f(0,0), p_idleTex),
								   Entity(Vector2f(0,30), p_idleTex),
								   Entity(Vector2f(0,60), p_idleTex),
								   Entity(Vector2f(0,90), p_idleTex) };
	
	{
		Entity ei(Vector2f(100, 50), p_idleTex);
		entity.push_back(ei);
	}

	bool isRunning = true;
	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.01f;
	float currentTime = utils::hireTimeInSeconds();

	while (isRunning) {
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= timeStep) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					isRunning = false;
			}

			accumulator -= timeStep;
		}

		const float alpha = accumulator / timeStep;

		window.clear();
		for (Entity& e : entity) {
			window.render(e);
		}
		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if (frameTicks < 1000 / window.getRefreshRate()) {
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}
	}

	window.clean();
	SDL_Quit();

	return 0;
}