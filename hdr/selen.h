#ifndef SELEN_H
#define SELEN_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

enum GameState {TITLE, GAMEPLAY, BATTLE} extern currentState;
/*
123
6 4
789
*/
enum Direction {NW, N, NE, W, E, SW, S, SE};

typedef struct Sprite {
	SDL_Texture *texture;
	SDL_Rect rect;
} Sprite;

extern SDL_bool gameRunning;

extern SDL_Window *win;
extern SDL_Renderer *ren;

extern Uint32 deltaTime;

extern SDL_Point mousePos;

TTF_Font *FontRegular(Uint8 size);

void Delay(Uint32 startTicks);
void GlobalInputHandler(SDL_Event event);
Sprite SpriteFromImage(char *imagePath);
Sprite SpriteFromText(TTF_Font *font, const char *text, SDL_Color fg);
Sprite UpdateSpriteFromText(Sprite sprite, TTF_Font *font, const char *text, SDL_Color fg);
SDL_bool CursorInSprite(Sprite sprite);
void RenderCopySprite(Sprite sprite);

void Title();
void Gameplay();
void Battle();

#endif