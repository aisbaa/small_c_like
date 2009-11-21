NAME   = smallclike

CPP    = g++
CC     = g++
CFLAGS = -Wall -c
LFALGS = -g

INNER_LANG_NAME   = inner_lang_gen.i
INNER_LANG_SOURCE = inner_lang_human.c
INNER_LANG_VALUES = inner_lang_values.h

DEMO_DIR = demo

SRCCPP = scanner.cpp rulemaster.cpp rulepawn.cpp token.cpp textstream.cpp innerLang.cpp position.cpp
HDRCPP = $(SRCCPP:.cpp=.h)

SRCC = ascii_info.c
HDRC = $(SRCCPP:.c=.h)

HDRS = $(HDRCPP) $(HDRC)
OBJS = $(SRCCPP:.cpp=.o) $(SRCC:.c=.o)
MAIN = $(OBJS) main.o 

all: compile innerLang run

compile: $(MAIN)
	$(CC) $(LFLAGS) $(MAIN) -o $(NAME)

.cpp.o:
	$(CPP) $(CFLAGS) $<

.c.o:
	$(CC) $(CFLAGS) $<

run:
	./$(NAME) $(DEMO_DIR)/simple.c
#	./$(NAME) $(DEMO_DIR)/example.c
#	./$(NAME) $(DEMO_DIR)/stress.c

innerLang: $(INNER_LANG_VALUES)
	gcc -E $(INNER_LANG_SOURCE) -o $(INNER_LANG_NAME)

clean:
	rm -fr *~ *.o *.gch
	rm -f $(NAME)
	rm -f $(INNER_LANG_NAME)

