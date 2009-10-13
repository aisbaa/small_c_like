#CPPUNIT_PATH=/opt/cppunit

NAME   = test
CC     = g++
CFLAGS = -Wall -c
LFLAGS = -Llib -lstdc++ -lcppunit -ldl

TESTFILES   = main.cpp
TESTOBJECTS = $(TESTFILES:.cpp=.o)

BASSESOURCE  = textstream_test.cpp ../textstream.cpp
BASEHEADERS  = $(BASSESOURCE:.cpp=.h)
BUILDOBJECTS = $(BASSESOURCE:.cpp=.o)
LINKOBJECTS  = textstream_test.o textstream.o

all: clean compile run

compile: $(TESTOBJECTS) $(BUILDOBJECTS)
	$(CC) -o $(NAME) $(TESTOBJECTS) $(LINKOBJECTS) $(LFLAGS)

.cpp.o: $.cpp $(BASEHEADERS)
	$(CC) $(CFLAGS) -c $<

run:
	./$(NAME)

clean:
	rm -f *~ *.o
	rm -f $(NAME)
