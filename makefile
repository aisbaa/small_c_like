NAME   = smallclike

CC     = g++
CFLAGS = -Wall

SRC    = scaner.cpp
HDR    = $(SRC: .cpp=.h)
OBJS   = $(SRC: .cpp=.o)
OBJS  += main.o

all: clean compiler

compiler: $(OBJS)
	$(CC) $(OBJS) -g -o $(NAME)


.cpp.o: $*.cpp $(HDR)
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	rm -fr *~ *.o
	rm -f $(NAME)

