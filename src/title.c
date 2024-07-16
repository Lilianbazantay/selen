#include "selen.h"

void Title() {
	loopRunning = SDL_TRUE;

	SDL_Surface *backgroundSurf = IMG_Load("res/images/background/title.png");
	SDL_Texture *backgroundTex = SDL_CreateTextureFromSurface(ren, backgroundSurf);
	SDL_FreeSurface(backgroundSurf);

	float tempAlpha = 0;
	SDL_Color color = {255, 255, 255, tempAlpha};

	TTF_Font* fontTitle = FontRegular(64);

	Sprite startSprite = SpriteFromText(fontTitle, "Start", color);
	startSprite.rect.x = 869 - startSprite.rect.w;
	startSprite.rect.y = 208;

	Sprite startSpriteHover = SpriteFromText(fontTitle, "Start", (SDL_Color){255, 255, 0, 255});
	startSpriteHover.rect.x = 869 - startSpriteHover.rect.w;
	startSpriteHover.rect.y = 208;

	Sprite quitSprite = SpriteFromText(fontTitle, "Quit", color);
	quitSprite.rect.x = 869 - quitSprite.rect.w;
	quitSprite.rect.y = 304;

	Sprite quitSpriteHover = SpriteFromText(fontTitle, "Quit", (SDL_Color){255, 255, 0, 255});
	quitSpriteHover.rect.x = 869 - quitSpriteHover.rect.w;
	quitSpriteHover.rect.y = 304;

	SDL_Event event;
	while (loopRunning) {
		GlobalLoopStart();

		while (SDL_PollEvent(&event)) {
			GlobalInputHandler(event);
			if (event.type == SDL_MOUSEBUTTONDOWN) if (event.button.button == SDL_BUTTON_LEFT) {
				if (CursorInSprite(startSprite)) {
					currentState = GAMEPLAY;
					loopRunning = SDL_FALSE;
				} else if (CursorInSprite(quitSprite)) {
					gameRunning = SDL_FALSE;
					loopRunning = SDL_FALSE;
				}
			}
		}

		if (tempAlpha < 255) {
			tempAlpha += 255.f * deltaTime * 0.002;
			if (tempAlpha > 255) tempAlpha = 255;
			color.a = tempAlpha;
			startSprite = UpdateSpriteFromText(startSprite, fontTitle, "Start", color);
			quitSprite = UpdateSpriteFromText(quitSprite, fontTitle, "Quit", color);
		}

		if (CursorInSprite(startSprite)) RenderCopySprite(startSpriteHover);
		else RenderCopySprite(startSprite);
		if (CursorInSprite(quitSprite)) RenderCopySprite(quitSpriteHover);
		else RenderCopySprite(quitSprite);

		GlobalLoopEnd();
	}

	SDL_DestroyTexture(startSprite.texture);
	SDL_DestroyTexture(startSpriteHover.texture);
	SDL_DestroyTexture(quitSprite.texture);
	SDL_DestroyTexture(quitSpriteHover.texture);
	TTF_CloseFont(fontTitle);
}