/**
 * innerLang header
 * 
 * Contains inner lang values.
 * File will be included, preprocessed
 * and saved as grammar.i file.
 */

#ifndef SMALL_C_LIKE_INNER_LANG_VALUES
#define SMALL_C_LIKE_INNER_LANG_VALUES

#define MAIN 1
#define STRUCT_DEC 2
#define INT 3
#define CHAR 4
#define FOR_DEC 5
#define WHILE_DEC 6
#define PRINTF_DEC 7
#define SCANF 8
#define IF_DEC 9
#define ELSE 10
#define RETURN 11
#define TRUE 12
#define FALSE 13
#define BRACE 14
#define OPEN_BRACE 15
#define CLOSE_BRACE 16
#define EMPTY_BLOCK 17
#define BEGIN 18
#define END 19
#define SQUARE_BRACKETS 20
#define SQUARE_BRACKET_OPEN 21
#define SQUARE_BRACKET_CLOSE 22
#define EQUALITY 23
#define IS_EQUAL_TO 24
#define NOT_EQUAL_TO 25
#define GREATER_OR_EQUAL 26
#define LESS_OR_EQUAL 27
#define GREATER 28
#define LESS 29
#define AND 30
#define OR 31
#define ADD 32
#define SUB 33
#define DIVISION 34
#define MODULUS 35
#define MULTIPLICATION 36
#define SEMICOLON 37
#define COMMA 38
#define COLON 39
#define DOT 40
#define VOID 41

#endif

#ifndef SMALL_C_LIKE_INNER_BNF_VALUES
#define SMALL_C_LIKE_INNER_BNF_VALUES

#define INIT_STATE 1000

#define POP 1001

#define _ID_VAL_ 1002
#define _INT_VAL_ 1003
#define _CHAR_VAL_ 1004
#define _STR_VAL_ 1005

#define UNDEFINED -1

#endif

#ifndef SMALL_C_LIKE_SEMANTIC_ACTION_VALUES
#define SMALL_C_LIKE_SEMANTIC_ACTION_VALUES

#define OUTPUT_SIGNLE 1
#define OUTPUT_QUEUE  2
#define PUSH_TO_STACK 3

#define REGISTRATE_SINGLE 4
#define REGISTRATE_START  5
#define REGISTRATE_END    6

#define AUTO 10

/* these are cheaty values*/
#define DONT_CHECK  0 // dont check the type of poped item
#define DONT_PUSH   0 // dont push new token to stack

#define DONT_OUTPUT # // dont write any stuff to output
#define DONT_OUTPUT_SC "#" // dont write any stuff to output

#define DONT_PUSH 0
#define DONT_PUSH_SC "DONT_PUSH"

#define semanticClass_Variable 0
#define semanticClass_Structur 1
#define semanticClass_Function 2

#endif
