#include "selen.h"

void Title() {
	SDL_bool titleRunning = SDL_TRUE;

	SDL_Surface *backgroundSurf = IMG_Load("res/images/background/title.png");
	SDL_Texture *backgroundTex = SDL_CreateTextureFromSurface(ren, backgroundSurf);
	SDL_FreeSurface(backgroundSurf);

	float tempAlpha;
	SDL_Color startColor = {255, 255, 255, 0};
	SDL_Color quitColor = {255, 255, 255, 0};

	SDL_Surface *startSurf = TTF_RenderText_Blended(fontRegular, "Start", startColor);
	SDL_Rect startRect = (SDL_Rect){869 - startSurf->w, 208, startSurf->w, startSurf->h};

	SDL_Surface *quitSurf = TTF_RenderText_Blended(fontRegular, "Quit", quitColor);
	SDL_Rect quitRect = (SDL_Rect){869 - quitSurf->w, 304, quitSurf->w, quitSurf->h};

	SDL_Texture *startTex, *quitTex;

	SDL_Point mousePos = {};

	Uint32 startTicks, passedTicks;
	SDL_Event event;

	while (titleRunning) {
		startTicks = SDL_GetTicks();
		quitColor.b = 255;

		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					gameRunning = SDL_FALSE;
					titleRunning = SDL_FALSE;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (SDL_PointInRect(&mousePos, &startRect)) {
							currentState = GAMEPLAY;
							titleRunning = SDL_FALSE;
						} else if (SDL_PointInRect(&mousePos, &quitRect)) {
							gameRunning = SDL_FALSE;
							titleRunning = SDL_FALSE;
						}
					}
			}
			GlobalInputHandler(event);
		}

		if (tempAlpha < 255) {
			tempAlpha += 255.f / FPS * 2;
			if (tempAlpha > 255) tempAlpha = 255;
			startColor.a = tempAlpha;
			quitColor.a = tempAlpha;
		}

		startColor.b = SDL_PointInRect(&mousePos, &startRect) ? 0 : 255;
		quitColor.b = SDL_PointInRect(&mousePos, &quitRect) ? 0 : 255;

		startSurf = TTF_RenderText_Blended(fontRegular, "Start", startColor);
		startTex = SDL_CreateTextureFromSurface(ren, startSurf);

		quitSurf = TTF_RenderText_Blended(fontRegular, "Quit", quitColor);
		quitTex = SDL_CreateTextureFromSurface(ren, quitSurf);

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, startTex, NULL, &startRect);
		SDL_RenderCopy(ren, quitTex, NULL, &quitRect);
		SDL_RenderPresent(ren);

		SDL_FreeSurface(startSurf);
		SDL_FreeSurface(quitSurf);
		SDL_DestroyTexture(startTex);
		SDL_DestroyTexture(quitTex);

		passedTicks = SDL_GetTicks() - startTicks;
		if (passedTicks < deltaTime) SDL_Delay(deltaTime - passedTicks);
	}
}