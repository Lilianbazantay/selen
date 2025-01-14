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
	char* name;
	Uint8 posX;
	Uint8 posY;
	enum Direction direction;
	struct Stats stats;
	Sprite sprite;
	SDL_bool isEnemy;
} Entity;

static Uint16 queueWidth = 0;
static Entity queue[394];

static Uint8 TILE_WIDTH = 32;
static Uint8 TILE_HEIGHT = 18;

void DrawEntity(Entity entity) {
	// entity.sprite.rect.w should not be higher than 64
	SDL_Rect rect;
	entity.sprite.rect.x = (entity.posX - entity.posY) * TILE_WIDTH + 32;
	entity.sprite.rect.y = (entity.posX + entity.posY) * TILE_HEIGHT + 46 - entity.sprite.rect.h;
	SDL_RenderCopy(ren, entity.sprite.texture, NULL, &entity.sprite.rect);
}

void DrawTerrain() {
	SDL_SetRenderDrawColor(ren, 255, 213, 6, 255);
	Uint16 baseX, baseY;
	for (Uint8 y = 0; y < 15; ++y) for (Uint8 x = 0; x < 15; ++x) {
		baseX = 32 + 64 * x;
		baseY = 32 + 36 * y;
		SDL_Point points[5] = {
			{baseX, baseY}, {baseX + 32, baseY - 18}, {baseX + 64, baseY}, {baseX + 32, baseY + 18}, {baseX, baseY}
		};
		SDL_RenderDrawLines(ren, points, 5);
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

double radians(double degree) {
	return degree * M_PI / 180;
}

void Battle() {
	loopRunning = SDL_TRUE;

	// test
	struct Stats selenStats = {1000, 100, 100, 50, 1000, 100, 100, 50, 0};
	Sprite selenSprite = SpriteFromImage("res/images/characters/selen.png");
	Entity selen = {0, "Selen", 14, 0, NW, selenStats, selenSprite, SDL_FALSE};
	struct Stats slimeStats = {200, 100, 100, 50, 200, 100, 100, 50, 0};
	Sprite slimeSprite = SpriteFromImage("res/images/monsters/slime.png");
	Entity slime = {0, "Slime", 0, 0, SE, slimeStats, slimeSprite, SDL_TRUE};
	queue[0] = selen;
	queue[1] = slime;
	queueWidth = 2;

	Sint16 baseX, baseY;
	Sint16 cellX, cellY;

	SDL_Event event;
	while (loopRunning) {
		GlobalLoopStart();

		while (SDL_PollEvent(&event)) {
			GlobalInputHandler(event);
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						SDL_Log("CELL: x = %i, y = %i", cellX, cellY);
						break;
					case SDL_BUTTON_RIGHT:
						SDL_Log("BASE: x = %i, y = %i", baseX, baseY);
						break;
				}
			}
		}

		Uint16 x = mousePos.x - 32;
		Uint16 y = mousePos.y - 14;
		cellX = (x / TILE_WIDTH + y / TILE_HEIGHT) / 2;
		cellY = (y / TILE_HEIGHT - x / TILE_WIDTH) / 2;
		baseX = (cellX - cellY) * TILE_WIDTH + 32;
		baseY = (cellX + cellY) * TILE_HEIGHT + 32;
		if (baseX >= 32 && baseX <= 928 && baseY >= 32 && baseY <= 536) {
			SDL_SetRenderDrawColor(ren, 0, 127, 255, 255);
			for (Uint8 height = 18; height > 0; --height) {
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
		for (Uint8 entityIdx = 0; entityIdx < queueWidth; ++entityIdx) DrawEntity(queue[entityIdx]);

		GlobalLoopEnd();
	}

	for (Uint8 entityIdx = 0; entityIdx < queueWidth; ++entityIdx) SDL_DestroyTexture(queue[entityIdx].sprite.texture);
}
