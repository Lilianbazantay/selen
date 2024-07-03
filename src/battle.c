#include <math.h>
#include <stdlib.h>

#include "selen.h"

typedef struct Entity {
	Uint16 ID;
	Uint8 x;
	Uint8 y;
	Uint16 maxHP;
	Uint8 maxAP;
	Uint16 maxATK;
	Uint16 maxDEF;
	int HP;
	int AP;
	int ATK;
	int DEF;
	SDL_bool isEnemy;
	SDL_Texture *texture;
} Entity;

static int queueWidth = 0;
static Entity *queue[225];

Entity *CreateEntity(
	Uint16 ID, Uint8 x, Uint8 y, Uint16 maxHP, Uint16 maxAP, Uint16 maxATK, Uint16 maxDEF, SDL_bool isEnemy, char *imagePath
	) {
	SDL_Surface *surface = IMG_Load(imagePath);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	Entity *entity = malloc(sizeof(Entity));
	entity->ID = ID;
	entity->x = x;
	entity->y = y;
	entity->maxHP = maxHP;
	entity->maxAP = maxAP;
	entity->maxATK = maxATK;
	entity->maxDEF = maxDEF;
	entity->HP = maxHP;
	entity->AP = maxAP;
	entity->ATK = maxATK;
	entity->DEF = maxDEF;
	entity->isEnemy = isEnemy;
	entity->texture = texture;
	return entity;
}

void DrawEntity(Entity *entity) {
	SDL_RenderCopy(ren, entity->texture, NULL, &(SDL_Rect){32 + 32 * entity->x, 14 + 32 * entity->y, 64, 36});
}

void DrawTerrain() {
	SDL_SetRenderDrawColor(ren, 255, 213, 6, 255);
	Uint16 baseX, baseY;
	for (Uint8 y = 0; y < 15; y++) {
		for (Uint8 x = 0; x < 15; x++) {
			baseX = 32 + 64 * x;
			baseY = 32 + 36 * y;
			SDL_Point points[5] = {
				{baseX, baseY}, {baseX + 32, baseY - 18}, {baseX + 64, baseY}, {baseX + 32, baseY + 18}, {baseX, baseY}
			};
			SDL_RenderDrawLines(ren, points, 5);
		}
	}
}

void Battle() {
	SDL_bool battleRunning = SDL_TRUE;

	SDL_Point mousePos;

	// test
	Entity *slime = CreateEntity(0, 0, 0, 100, 100, 0, 0, SDL_TRUE, "res/images/monsters/slime.png");
	queue[0] = slime;
	queueWidth = 1;

	Uint8 cellX, cellY;
	float tempCellX, tempCellY;
	Uint16 baseX, baseY;
	Uint32 startTicks, passedTicks;

	SDL_Event event;
	while (battleRunning) {
		startTicks = SDL_GetTicks();

		SDL_GetMouseState(&mousePos.x, &mousePos.y);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = SDL_FALSE;
				battleRunning = SDL_FALSE;
			}
			GlobalInputHandler(event);
		}

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		if (mousePos.x >= 32 && mousePos.y >= 18 && mousePos.x <= 992 && mousePos.y <= 572) {
			if (mousePos.x < 64 && mousePos.y < 32) {
				cellX = 0;
				cellY = 0;
			} else {
				tempCellX = (mousePos.x - 64.f) / 32;
				tempCellY = (mousePos.y - 32.f) / 18;
				cellX = round(tempCellX);
				cellY = round(tempCellY);
				if (cellX % 2 != cellY % 2) {
					tempCellX = cellX - tempCellX;
					tempCellY = cellY - tempCellY;
					if (fabs(tempCellX) >= fabs(tempCellY)) {
						if (tempCellX >= 0) cellX -= 1;
						else cellX += 1;
					} else {
						if (tempCellY >= 0) cellY -= 1;
						else cellY += 1;
					}
				}
			}
			baseX = 32 + 32 * cellX;
			baseY = 32 + 18 * cellY;
			SDL_SetRenderDrawColor(ren, 0, 127, 255, 255);
			for (Uint8 height = 18; height > 0; height--) {
				SDL_Point points[5] = {
					{baseX, baseY}, {baseX + 32, baseY - height}, {baseX + 64, baseY}, {baseX + 32, baseY + height},
					{baseX, baseY}
				};
				SDL_RenderDrawLines(ren, points, 5);
			}
			SDL_RenderDrawLines(ren, (SDL_Point[2]){{baseX, baseY}, {baseX + 64, baseY}}, 2);
		}
		DrawTerrain();
		DrawEntity(slime);
		SDL_RenderPresent(ren);

		passedTicks = SDL_GetTicks() - startTicks;
		if (passedTicks < deltaTime) SDL_Delay(deltaTime - passedTicks);
	}
	free(slime);	// test
}