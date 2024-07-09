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

Sprite SpriteFromImage(char *imagePath) {
	SDL_Surface *surface = IMG_Load(imagePath);
	Sprite sprite = {SDL_CreateTextureFromSurface(ren, surface), (SDL_Rect){.w=surface->w, .h=surface->h}};
	SDL_FreeSurface(surface);
	return sprite;
}

Sprite SpriteFromText(TTF_Font *font, const char *text, SDL_Color fg) {
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, fg);
	Sprite sprite = {SDL_CreateTextureFromSurface(ren, surface), (SDL_Rect){.w=surface->w, .h=surface->h}};
	SDL_FreeSurface(surface);
	return sprite;
}

Sprite UpdateSpriteFromText(Sprite sprite, TTF_Font *font, const char *text, SDL_Color fg) {
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, fg);
	sprite.texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	return sprite;
}

SDL_bool CursorInSprite(Sprite sprite) {
	return SDL_PointInRect(&mousePos, &sprite.rect);
}

void RenderCopySprite(Sprite sprite) {
	SDL_RenderCopy(ren, sprite.texture, NULL, &sprite.rect);
}