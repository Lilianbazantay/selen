#include "selen.h"

void GlobalInputHandler(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_F11) {
			if (SDL_GetWindowFlags(win) & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(win, 0);
			else SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
		}
	}
}