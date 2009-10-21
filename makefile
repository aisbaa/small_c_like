NAME   = smallclike

CC     = g++
CFLAGS = -Wall -c
LFALGS = -g

SRCCPP = scanner.cpp rulemaster.cpp rulepawn.cpp token.cpp
HDRCPP = $(SRCCPP:.cpp=.h)

HDRS  = $(HDRCPP) ascii_info.h
OBJS  = $(SRCCPP:.cpp=.o) ascii_info.o
MAIN  = $(OBJS) main.o 

all: compile run

compile: $(MAIN)
	$(CC) $(LFLAGS) $(MAIN) -o $(NAME)


.cpp.o:
	$(CC) $(CFLAGS) $<

.c.o:
	$(CC) $(CFLAGS) $<

run:
	./$(NAME)

grammar: humangrammar.c innerLangValues.h
	gcc -E humangrammar.c -o grammar.i

clean:
	rm -fr *~ *.o
	rm -f $(NAME)

