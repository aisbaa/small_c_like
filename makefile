NAME   = smallclike

CPP    = g++
CC     = g++
CFLAGS = -Wall -c
LFALGS = -g

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

clean:
	rm -fr *~ *.o *.gch
	rm -f $(NAME)
	rm -f $(INNER_LANG_NAME)
	rm -f $(INNER_AUGMENT_GRAMMAR_NAME)

INNER_LANG_NAME   = inner_lang_gen.i
INNER_LANG_SOURCE = inner_lang_human.c
INNER_LANG_VALUES = inner_lang_values.h

innerLang: $(INNER_LANG_VALUES)
	gcc -E $(INNER_LANG_SOURCE)  | grep $"^#.*$" -v  > $(INNER_LANG_NAME)


INNER_AUGMENT_GRAMMAR_NAME = inner_augment_grammar_human_test.i
INNER_AUGMENT_GRAMMAR_SOURCE = inner_augment_grammar_human_test.c

augmentGrammar: $(INNER_AUGMENT_GRAMMAR)
	gcc -E $(INNER_AUGMENT_GRAMMAR_SOURCE)  | grep $"^#.*$" -v > $(INNER_AUGMENT_GRAMMAR_NAME)
