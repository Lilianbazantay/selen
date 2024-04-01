## MAKEFILE 
## main makefile for the selen project

NAME = selen

SRCS = main.cpp

# OBJS = $(SRCS:.cpp=.o)

CFLAGS = -Wall -Wextra -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME):
	g++ $(CFLAGS) -o exec $(SRCS) $(LDFLAGS)

# clean:
# 	rm -f $(OBJS)


re: clean all

.PHONY : all clean re
