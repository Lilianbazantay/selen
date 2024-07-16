#include "selen.h"

void Gameplay() {
	loopRunning = SDL_TRUE;

	SDL_Event event;
	while (loopRunning) {
		GlobalLoopStart();

		while (SDL_PollEvent(&event)) {
			GlobalInputHandler(event);
		}

		// test battle
		loopRunning = SDL_FALSE;
		currentState = BATTLE;

		GlobalLoopEnd();
	}
}