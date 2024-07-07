#include "selen.h"

void Delay(Uint32 startTicks) {
	Uint32 passedTicks = SDL_GetTicks() - startTicks;
	if (passedTicks < deltaTime) SDL_Delay(deltaTime - passedTicks);
}

void GlobalInputHandler(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_F11) {
			if (SDL_GetWindowFlags(win) & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(win, 0);
			else SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
		}
	}
}