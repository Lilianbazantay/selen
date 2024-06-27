#include "selen.h"

static SDL_bool gameplayRunning = SDL_TRUE;

void Gameplay(SDL_Window *win, SDL_Renderer *ren) {
	SDL_Event event;
	while (gameplayRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = SDL_FALSE;
				gameplayRunning = SDL_FALSE;
			}
		}
		SDL_RenderClear(ren);
		SDL_RenderPresent(ren);
	}
}