NAME   = smallclike
RWTOOL = rw

CPP    = g++
CC     = g++
CFLAGS = -Wall -pedantic -c
LFALGS = -g

DEMO_DIR = demo

SRCCPP = scanner.cpp rulemaster.cpp rulepawn.cpp token.cpp textstream.cpp innerLang.cpp position.cpp syntax.cpp analizer.cpp
HDRCPP = $(SRCCPP:.cpp=.h)

SRCC = ascii_info.c
HDRC = $(SRCCPP:.c=.h)

RWOBJ = rewritertool.o ascii_info.o

HDRS = $(HDRCPP) $(HDRC)
OBJS = $(SRCCPP:.cpp=.o) $(SRCC:.c=.o)
MAIN = $(OBJS) main.o 

all: compile innerLang augmentGrammar run

compile: $(MAIN)
	$(CPP) $(LFLAGS) $(MAIN) -o $(NAME)

rwtool: $(RWOBJ)
	$(CPP) $(LFLAGS) $(RWOBJ) -o $(RWTOOL)

.cpp.o:
	$(CPP) $(CFLAGS) $<

.c.o:
	$(CC) $(CFLAGS) $<

run: innerLang augmentGrammar
	./$(NAME) $(DEMO_DIR)/simple.c
#	./$(NAME) $(DEMO_DIR)/example.c
#	./$(NAME) $(DEMO_DIR)/stress.c

clean:
	make -C $(DEMO_DIR)
	rm -fr *~ *.o *.gch
	rm -f $(NAME)
	rm -f $(RWTOOL)
	rm -f $(INNER_LANG_NAME)
	rm -f $(INNER_AUGMENT_GRAMMAR_NAME)

INNER_LANG_NAME   = inner_lang_gen.i
INNER_LANG_SOURCE = inner_lang_human.c
INNER_LANG_VALUES = inner_lang_values.h

innerLang: $(INNER_LANG_VALUES)
	gcc -E $(INNER_LANG_SOURCE)  | grep $"^#.*$" -v  > $(INNER_LANG_NAME)

INNER_AUGMENT_GRAMMAR_NAME = inner_augment_grammar_human.i
INNER_AUGMENT_GRAMMAR_SOURCE = inner_augment_grammar_human.c

augmentGrammar: rwtool $(INNER_AUGMENT_GRAMMAR)
	- gcc -E $(INNER_AUGMENT_GRAMMAR_SOURCE) \
	| grep '^#.*$$' -v \
	| grep '^ *$$' -v \
	| awk '{ print $$1 " " $$3 " " $$4 " " $$5 }' \
	| ./rw > $(INNER_AUGMENT_GRAMMAR_NAME)
