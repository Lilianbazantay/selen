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

static int *actionQueue;

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
	SDL_SetRenderDrawColor(ren, 255, 215, 0, 255);
	int baseX, baseY;
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 15; x++) {
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

	// test
	Entity *slime = CreateEntity(0, 0, 0, 100, 100, 0, 0, SDL_TRUE, "res/images/monsters/slime.png");

	Uint32 startTicks, passedTicks;

	SDL_Event event;
	while (battleRunning) {
		startTicks = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = SDL_FALSE;
				battleRunning = SDL_FALSE;
			}
			GlobalInputHandler(event);
		}

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		DrawTerrain();
		DrawEntity(slime);
		SDL_RenderPresent(ren);

		passedTicks = SDL_GetTicks() - startTicks;
		if (passedTicks < deltaTime) SDL_Delay(deltaTime - passedTicks);
	}
	free(slime);	// test
}