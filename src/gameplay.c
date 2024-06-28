#include "selen.h"

void Gameplay() {
	SDL_bool gameplayRunning = SDL_TRUE;

	SDL_Event event;
	while (gameplayRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = SDL_FALSE;
				gameplayRunning = SDL_FALSE;
			}
			GlobalInputHandler(event);
		}
		SDL_RenderClear(ren);
		SDL_RenderPresent(ren);
	}
}