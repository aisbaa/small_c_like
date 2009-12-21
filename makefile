NAME   = smallclike
RWTOOL = rw

CPP    = g++
CC     = g++
CFLAGS = -Wall -pedantic -c -g
LFALGS = -g

DEMO_DIR = demo

SRCCPP = scanner.cpp rulemaster.cpp rulepawn.cpp token.cpp textstream.cpp innerLang.cpp position.cpp syntax.cpp analizer.cpp semantic.cpp idTable.cpp
HDRCPP = $(SRCCPP:.cpp=.h)

SRCC = ascii_info.c
HDRC = $(SRCCPP:.c=.h)

RWOBJ = rewritertool.o ascii_info.o

HDRS = $(HDRCPP) $(HDRC)
OBJS = $(SRCCPP:.cpp=.o) $(SRCC:.c=.o)
MAIN = $(OBJS) main.o 

all: compile innerLang augmentGrammar semanticRuls run

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

INNER_LANG_NAME   = inner_lang_gen.i
INNER_LANG_SOURCE = inner_lang_human.c
INNER_LANG_VALUES = inner_lang_values.h

innerLang: $(INNER_LANG_VALUES)
	gcc -E $(INNER_LANG_SOURCE)  | grep $"^#.*$" -v  > $(INNER_LANG_NAME)

INNER_AUGMENT_GRAMMAR_SOURCE = inner_augment_grammar_human.c
INNER_AUGMENT_GRAMMAR_PREPROCESSED_FILE = inner_augment_grammar_gen.i
INNER_AUGMENT_GRAMMAR_STATE_HEADER_FILE = inner_augment_grammar_states.h

augmentGrammar: rwtool $(INNER_AUGMENT_GRAMMAR_SOURCE)
	gcc -E $(INNER_AUGMENT_GRAMMAR_SOURCE) \
	| grep '^#.*$$' -v \
	| grep '^ *$$' -v \
	| awk '{ print $$1 " " $$3 " " $$4 " " $$5 }' \
	| ./rw $(INNER_AUGMENT_GRAMMAR_STATE_HEADER_FILE) > $(INNER_AUGMENT_GRAMMAR_PREPROCESSED_FILE)

INNER_SEMANTIC_RULES_SOURCE = inner_semantic_rules.c
INNER_SEMANTIC_RULES_FILE   = inner_semantic_rules.i

semanticRuls: augmentGrammar $(INNER_AUGMENT_GRAMMAR_STATE_HEADER_FILE) $(INNER_SEMANTIC_RULES_SOURCE)
	gcc -E $(INNER_SEMANTIC_RULES_SOURCE) 2>/dev/null \
	| grep '^#.*$$' -v \
	| grep '^ *$$' -v > $(INNER_SEMANTIC_RULES_FILE)

clean:
	make -C $(DEMO_DIR)
	rm -fr *~ *.o *.gch
	rm -f $(NAME)
	rm -f $(RWTOOL)
	rm -f $(INNER_LANG_NAME)
	rm -f $(INNER_AUGMENT_GRAMMAR_PREPROCESSED_FILE)
	rm -f $(INNER_AUGMENT_GRAMMAR_STATE_HEADER_FILE)
