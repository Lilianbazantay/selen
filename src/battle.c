#include "selen.h"

void DrawTerrain() {
	SDL_SetRenderDrawColor(ren, 255, 215, 0, 255);
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 15; x++) {
			SDL_RenderDrawRect(ren, &(SDL_Rect){32 + 64 * x, 32 + 64 * y, 64, 64});
		}
	}
}

void Battle() {
	SDL_bool battleRunning = SDL_TRUE;

	Uint32 startTicks, passedTicks;

	SDL_Event event;
	while (battleRunning) {
		startTicks = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = SDL_FALSE;
				battleRunning = SDL_FALSE;
			}
			GlobalInputHandler(event);
		}

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		DrawTerrain();
		SDL_RenderPresent(ren);

		passedTicks = SDL_GetTicks() - startTicks;
		if (passedTicks < deltaTime) SDL_Delay(deltaTime - passedTicks);
	}
}