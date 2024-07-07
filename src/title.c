#include "selen.h"

void Title() {
	SDL_bool titleRunning = SDL_TRUE;

	SDL_Surface *backgroundSurf = IMG_Load("res/images/background/title.png");
	SDL_Texture *backgroundTex = SDL_CreateTextureFromSurface(ren, backgroundSurf);
	SDL_FreeSurface(backgroundSurf);

	float tempAlpha = 0;
	SDL_Color color = {255, 255, 255, tempAlpha};

	TTF_Font *fontTitle = FontRegular(64);

	SDL_Surface *startSurfHover = TTF_RenderText_Blended(fontTitle, "Start", (SDL_Color){255, 255, 0, 255});
	SDL_Rect startRect = (SDL_Rect){869 - startSurfHover->w, 208, startSurfHover->w, startSurfHover->h};

	SDL_Surface *quitSurfHover = TTF_RenderText_Blended(fontTitle, "Quit", (SDL_Color){255, 255, 0, 255});
	SDL_Rect quitRect = (SDL_Rect){869 - startSurfHover->w, 304, startSurfHover->w, startSurfHover->h};

	SDL_Texture *startTexHover = SDL_CreateTextureFromSurface(ren, startSurfHover);
	SDL_FreeSurface(startSurfHover);
	SDL_Texture *quitTexHover = SDL_CreateTextureFromSurface(ren, quitSurfHover);
	SDL_FreeSurface(quitSurfHover);

	SDL_bool deleteSurf = SDL_FALSE;
	SDL_Surface *startSurf, *quitSurf;
	SDL_Texture *startTex, *quitTex;

	SDL_Point mousePos = {};

	Uint32 startTicks;
	SDL_Event event;

	while (titleRunning) {
		startTicks = SDL_GetTicks();

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
			if (tempAlpha > 255) {
				tempAlpha = 255;
				deleteSurf = SDL_TRUE;
			}
			color.a = tempAlpha;
			startSurf = TTF_RenderText_Blended(fontTitle, "Start", color);
			startTex = SDL_CreateTextureFromSurface(ren, startSurf);
			quitSurf = TTF_RenderText_Blended(fontTitle, "Quit", color);
			quitTex = SDL_CreateTextureFromSurface(ren, quitSurf);
			if (deleteSurf) {
				SDL_FreeSurface(startSurf);
				SDL_FreeSurface(quitSurf);
			}
		}

		SDL_RenderClear(ren);

		if (SDL_PointInRect(&mousePos, &startRect)) SDL_RenderCopy(ren, startTexHover, NULL, &startRect);
		else SDL_RenderCopy(ren, startTex, NULL, &startRect);
		if (SDL_PointInRect(&mousePos, &quitRect)) SDL_RenderCopy(ren, quitTexHover, NULL, &quitRect);
		else SDL_RenderCopy(ren, quitTex, NULL, &quitRect);

		SDL_RenderPresent(ren);
		Delay(startTicks);
	}

	SDL_DestroyTexture(startTex);
	SDL_DestroyTexture(startTexHover);
	SDL_DestroyTexture(quitTex);
	SDL_DestroyTexture(quitTexHover);
	TTF_CloseFont(fontTitle);
}