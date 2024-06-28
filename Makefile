CC := gcc
CFLAGS := -g -Wall -Dmain=SDL_main
INCLUDE := -Ihdr/SDL2 -Ihdr
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -mwindows
LDFLAGS += -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32
LDFLAGS += -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
LDFLAGS += -lSDL2_image -lSDL2_ttf -lusp10 -lrpcrt4 -lselen

default: Selen.exe
	@echo "Successfully compiled!"

Selen.exe: src/main.c lib/libselen.a
	$(CC) $(CFLAGS) src/main.c $(INCLUDE) $(LDFLAGS) -o Selen.exe

lib/libselen.a: bld bld/global.o bld/title.o bld/gameplay.o
	ar -rcs lib/libselen.a bld/global.o bld/title.o bld/gameplay.o

bld/global.o: src/global.c
	$(CC) -c src/global.c $(INCLUDE) -o bld/global.o

bld/title.o: src/title.c
	$(CC) -c src/title.c $(INCLUDE) -o bld/title.o

bld/gameplay.o: src/gameplay.c
	$(CC) -c src/gameplay.c $(INCLUDE) -o bld/gameplay.o

bld:
	mkdir bld