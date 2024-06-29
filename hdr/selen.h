#ifndef SELEN_H
#define SELEN_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define FPS 60

enum GameState {TITLE, GAMEPLAY, BATTLE} extern currentState;

extern SDL_bool gameRunning;

extern SDL_Window *win;
extern SDL_Renderer *ren;

extern Uint32 deltaTime;

extern TTF_Font *fontRegular;

void GlobalInputHandler(SDL_Event event);

void Title();
void Gameplay();
void Battle();

#endif