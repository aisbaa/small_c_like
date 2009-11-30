#include "inner_lang_values.h"

/* Stack operation
 * + is push
 * * is push and check again
 *
 * - is pop
 * / is pop and check again
 *
 * ~ is reduction (top becomes)
 * | is reduction and check again
 *
 */

/*
new_state       stack_top  token      action
*/
INIT_STATE  ::= INIT_STATE INIT_STATE ~
INT         ::= INIT_STATE INT        +
INT         ::= INIT_STATE CHAR       +

/* variable declaration */
var_dec     ::= VAR_DEC_BLK INT +
var_dec     ::= VAR_DEC_BLK CHAR +
var_dec     ::= VAR_DEC_BLK _ID_VAL_ +

var_id      ::= var_dec _ID_VAL_ ~

var_id=     ::= var_id EQUALITY ~

var_id=-    ::= var_id= SUB ~

var_id=val  ::= var_id=- _INT_VAL_ ~
var_id=val  ::= var_id=  _INT_VAL_ ~
var_id=val  ::= var_id=  _CHAR_VAL_ ~

POP         ::= var_id SEMICOLON -
POP         ::= var_id=val SEMICOLON -

/* what goes after variable declaration */
var_dec     ::= VAR_DEC_BLK MAIN /
var_dec     ::= VAR_DEC_BLK STRUCT_DEC /
var_dec     ::= VAR_DEC_BLK FOR_DEC /
var_dec     ::= VAR_DEC_BLK WHILE_DEC /
var_dec     ::= VAR_DEC_BLK PRINTF_DEC /
var_dec     ::= VAR_DEC_BLK SCANF_DEC /
var_dec     ::= VAR_DEC_BLK IF_DEC /
var_dec     ::= VAR_DEC_BLK RETURN /
var_dec     ::= VAR_DEC_BLK _ID_VAL_ /
var_dec     ::= VAR_DEC_BLK END /

/* code block */
VAR_DEC_BLK ::= code_blk INT *
VAR_DEC_BLK ::= code_blk CHAR *

/* after code block */
POP         ::= code_blk END /

/* struct */
struct      ::= INIT_STATE STRUCT_DEC +
strct_name  ::= struct _ID_ ~
strct_name{ ::= strct_name BEGIN *
VAR_DEC_BLK ::= strct_name{ BEGIN +
POP         ::= strct_name{ END -

/* main */
main_i      ::= INT MAIN ~
main_(      ::= main_i OPEN_BRACE ~
main_()     ::= main_( CLOSE_BRACE ~
main_(){    ::= main_() BEGIN |
code_blk    ::= main_(){ BEGIN +
POP         ::= main_(){ END -


/* return */
return      ::= code_blk RETURN +
return_int  ::= return _INT_VAL_ ~
POP         ::= return_int SEMICOLON -

/* if () */
if          ::= code_blk IF_DEC +
if_(        ::= if OPEN_BRACE ~
if_(bool    ::= if_( TRUE ~
if_(bool    ::= if_( FALSE ~
if_(bool)   ::= if_(bool CLOSE_BRACE ~

/* if () { */
if(){}      ::= if_(bool) BEGIN |
code_blk    ::= if(){} BEGIN +

/* if () {} else */
if_else     ::= if(){} ELSE ~

code_blk    ::= if_else BEGIN ~

if          ::= if_else IF_DEC ~

/* if () {} and not else */
POP         ::= if(){} STRUCT_DEC /
POP         ::= if(){} INT /
POP         ::= if(){} CHAR /
POP         ::= if(){} FOR_DEC /
POP         ::= if(){} WHILE_DEC /
POP         ::= if(){} PRINTF_DEC /
POP         ::= if(){} SCANF_DEC /
POP         ::= if(){} IF_DEC /
POP         ::= if(){} RETURN /
