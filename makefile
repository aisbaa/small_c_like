NAME   = smallclike

CC     = g++
CFLAGS = -Wall -c
LFALGS = -g

SRC   = scanner.cpp innerLang.cpp token.cpp textstream.cpp
HDR   = $(SRC:.cpp=.h)
OBJS  = $(SRC:.cpp=.o)
MAIN  = $(OBJS) main.o

all: compile run

compile: $(MAIN)
	$(CC) $(LFLAGS) $(MAIN) -o $(NAME)


.cpp.o:
	$(CC) $(CFLAGS) $<

run:
	./$(NAME)

grammar: humangrammar.c innerLangValues.h
	gcc -E humangrammar.c -o grammar.i

clean:
	rm -fr *~ *.o
	rm -f $(NAME)

