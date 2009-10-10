NAME   = smallclike

CC     = g++
CFLAGS = -Wall

SRC    = scaner.cpp innerLang.cpp token.cpp stringinfo.cpp
HDR    = $(SRC: .cpp=.h)
OBJS   = $(SRC: .cpp=.o)
OBJS  += main.o

all: clean compiler

compiler: $(OBJS)
	$(CC) $(OBJS) -g -o $(NAME)


.cpp.o: $*.cpp $(HDR)
	$(CC) $(CFLAGS) -c $*.cpp

run:
	./$(NAME)

grammar: humangrammar.c innerLangValues.h
	gcc -E humangrammar.c -o grammar.i

clean:
	rm -fr *~ *.o
	rm -f $(NAME)

