## MAKEFILE 
## main makefile for the selen project

NAME = selen

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -Wall -Wextra -g

all: $(NAME)

$(NAME) : $(OBJS)
	gcc -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)


re: clean all

.PHONY : all clean re
