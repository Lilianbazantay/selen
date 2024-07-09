#include <math.h>
#include <stdlib.h>

#include "selen.h"

struct Stats {
	Uint16 maxHP;
	Uint8 maxAP;
	Uint16 maxATK;
	Uint16 maxDEF;
	int HP;
	int AP;
	int ATK;
	int DEF;
	Uint16 delay;
};

typedef struct Entity {
	Uint16 ID;
	char *name;
	Uint8 posX;
	Uint8 posY;
	enum Direction direction;
	struct Stats stats;
	Sprite sprite;
	SDL_bool isEnemy;
} Entity;

static int queueWidth = 0;
static Entity queue[394];

void DrawEntity(Entity entity) {
	// entity.sprite.rect.w should not be higher than 64
	SDL_Rect rect;
	if (entity.sprite.rect.x % 2 == entity.sprite.rect.y % 2) {
		entity.sprite.rect.x = 32 + 32 * entity.posX;
		entity.sprite.rect.y = 50 + 18 * entity.posY - entity.sprite.rect.h;
	} else {
		entity.sprite.rect.x = 64 + 32 * entity.posX;
		entity.sprite.rect.y = 68 + 18 * entity.posY - entity.sprite.rect.h;
	}
	SDL_RenderCopy(ren, entity.sprite.texture, NULL, &entity.sprite.rect);
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

int compareByDelay(const void *first, const void *second) {
	Entity entityFirst = *(Entity *)first;
	Entity entitySecond = *(Entity *)second;
	return entityFirst.stats.delay - entitySecond.stats.delay;
}

int compareByHeight(const void *first, const void *second) {
	Entity entityFirst = *(Entity *)first;
	Entity entitySecond = *(Entity *)second;
	return entityFirst.sprite.rect.h - entitySecond.sprite.rect.h;
}

void Battle() {
	SDL_bool battleRunning = SDL_TRUE;

	SDL_Point mousePos;

	// test
	struct Stats selenStats = {1000, 100, 100, 50, 1000, 100, 100, 50, 0};
	Entity selen = {0, "Selen", 5, 5, NW, selenStats, SpriteFromImage("res/images/characters/selen.png"), SDL_FALSE};
	struct Stats slimeStats = {200, 100, 100, 50, 200, 100, 100, 50, 0};
	Entity slime = {0, "Slime", 2, 2, SE, slimeStats, SpriteFromImage("res/images/monsters/slime.png"), SDL_TRUE};
	queue[0] = selen;
	queue[1] = slime;
	queueWidth = 2;

	Uint8 cellX, cellY;
	float tempCellX, tempCellY;
	Uint16 baseX, baseY;
	Uint32 startTicks;

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
		qsort(queue, queueWidth, sizeof(Entity), compareByHeight);
		for (Uint8 entityIdx = 0; entityIdx < queueWidth; entityIdx++)
			DrawEntity(queue[entityIdx]);

		SDL_RenderPresent(ren);
		Delay(startTicks);
	}

	for (Uint8 entityIdx = 0; entityIdx < queueWidth; entityIdx++)
		SDL_DestroyTexture(queue[entityIdx].sprite.texture);
}