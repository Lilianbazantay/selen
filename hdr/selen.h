#ifndef SELEN_H
#define SELEN_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define FPS 60

extern SDL_bool gameRunning;

enum GameState {TITLE, GAMEPLAY} extern currentState;

void GlobalInputHandler(SDL_Window *win, SDL_Event event);

void Title(SDL_Window *win, SDL_Renderer *ren);
void Gameplay(SDL_Window *win, SDL_Renderer *ren);

#endif