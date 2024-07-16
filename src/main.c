#include "selen.h"

enum GameState currentState = TITLE;

SDL_bool gameRunning = SDL_TRUE;
SDL_bool loopRunning;

Uint32 deltaTime = 17;
Uint32 startTicks;

SDL_Window* win;
SDL_Renderer* ren;

SDL_Point mousePos;

int SDL_main(int argc, char** argv) {
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	win = SDL_CreateWindow("Selen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_ALLOW_HIGHDPI);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	while (gameRunning) {
		switch (currentState) {
			case TITLE:
				Title();
				break;
			case GAMEPLAY:
				Gameplay();
				break;
			case BATTLE:
				Battle();
				break;
		}
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}