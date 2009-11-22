#include "inner_lang_values.h"

$           ::= $

$           ::= CHAR

$           ::= INT

INT         ::= MAIN

main_dec0   ::= INT MAIN
main_dec1   ::= main_dec0 OPEN_BRACE
main_dec2   ::= main_dec1 CLOSE_BRACE
main_dec3   ::= main_dec2 BEGIN
main_func   ::= main_dec3 END

POP         ::= main_func

var_dec0    ::= INT ID
var_dec0    ::= CHAR ID

var_dec1    ::= var_dec0 EQUALITY

var_dec2    ::= var_dec1 INT_VAL
var_dec2    ::= var_dec1 CHAR_VAL

var_decl    ::= var_dec0 SEMICOLON
var_decl    ::= var_dec2 SEMICOLON

POP         ::= var_decl
