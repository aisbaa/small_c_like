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

/* padaryta
   
   aritmetika
   variable declaration

   struct

   main

   if [ else [if] ]

   return

*/

/* reikia padaryti

   bool statement (reiÅ¡kiniai kuriÅ³ atsakymas true arba false)
   masyvai (deklaracija ir panaudojimas)
   f-jos (deklaracija ir panaudojimas)
   scanf printf

 */


/*
new_state       stack_top  token      action
*/
INIT_STATE   ::= INIT_STATE INIT_STATE ~
INT          ::= INIT_STATE INT        +
INT          ::= INIT_STATE CHAR       +
INT          ::= INIT_STATE VOID       +

/*
 * GENERIC
 */

id_useage    ::= code_blk _ID_VAL_ +

/* code block */
VAR_DEC_BLK  ::= code_blk INT *
VAR_DEC_BLK  ::= code_blk CHAR *

/* after code block */
POP          ::= code_blk END /

/*
 * BOOL ARITMETHIC
 */

/* direct */
bbool        ::= bool TRUE ~
bbool        ::= bool FALSE ~

bbool|&      ::= bbool OR ~
bbool|&      ::= bbool AND ~

bbooli       ::= bbool|& _ID_VAL_ ~
bbool        ::= bbool|& TRUE ~
bbool        ::= bbool|& FALSE ~

/* indirect */
bbooli       ::= bool _ID_VAL_ ~
bbool|&      ::= bbooli OR ~
bbool|&      ::= bbooli AND ~

bboolic      ::= bbooli ADD |
aritm_id+    ::= bboolic ADD +

/* what goes after variable declaration */
POP          ::= bbool CLOSE_BRACE /
POP          ::= bbooli CLOSE_BRACE /

/*
 * ARITMETHIC
 */
/* has no function and array useage */

/*
 * LAYERED ARITMETHIC
 */

/* ADDING ARITM LAYER */

/* first is open brace ( */
aritm(       ::= aritm  OPEN_BRACE |
aritm        ::= aritm( OPEN_BRACE +

/* after first id sign */
aritm_id+-(  ::= aritm_id+-  OPEN_BRACE |
aritm        ::= aritm_id+-( OPEN_BRACE +

aritm_id*(   ::= aritm_id*  OPEN_BRACE |
aritm        ::= aritm_id*( OPEN_BRACE +

/* REMOVING ARITM LAYER */
POP          ::= aritm_id+-id CLOSE_BRACE /
POP          ::= aritm_id CLOSE_BRACE /

/* REDUCTION AFTER LAYER REMUVAL */

/* closing brace ) */
aritm_id     ::= aritm( CLOSE_BRACE ~
aritm_id+-id ::= aritm_id+-( CLOSE_BRACE ~
aritm_id     ::= aritm_id*( CLOSE_BRACE ~

/* NON LAYERED ARITM */

/* first is minus sign */
aritm-       ::= aritm SUB ~

aritm_id     ::= aritm- _INT_VAL_ ~
aritm_id     ::= aritm- _ID_VAL_ ~

/* first is value or id */
aritm_id     ::= aritm _INT_VAL_ ~
aritm_id     ::= aritm _ID_VAL_ ~

/* use of structures */
aritm_strct  ::= aritm_id DOT +
aritm_str_id ::= aritm_strct _ID_VAL_ ~
aritm_strct  ::= aritm_str_id DOT ~

/* pop out struct use */
POP          ::= aritm_str_id ADD /
POP          ::= aritm_str_id SUB /
POP          ::= aritm_str_id MULTIPLICATION /
POP          ::= aritm_str_id DIVISION /
POP          ::= aritm_str_id MODULUS /

POP          ::= aritm_str_id SEMICOLON /
POP          ::= aritm_str_id COMMA /


/* + - after id or value */
aritm_id+-   ::= aritm_id ADD ~
aritm_id+-   ::= aritm_id SUB ~

/* id or value after + - sign */
aritm_id+-id ::= aritm_id+- _ID_VAL_ ~
aritm_id+-id ::= aritm_id+- _INT_VAL_ ~

/* + - after previous adition subtraction */
/* err condition */
aritm_id+-   ::= aritm_id+-id ADD ~
aritm_id+-   ::= aritm_id+-id SUB ~

/* mul div mod after id */
aritm_id*    ::= aritm_id MULTIPLICATION ~
aritm_id*    ::= aritm_id DIVISION ~
aritm_id*    ::= aritm_id MODULUS ~

/* id or value after mul div mod */
aritm_id     ::= aritm_id* _INT_VAL_ ~
aritm_id     ::= aritm_id* _ID_VAL_ ~

/* mul div mod after id add sub id */
aritm+*      ::= aritm_id+-id MULTIPLICATION ~
aritm+*      ::= aritm_id+-id DIVISION ~
aritm+*      ::= aritm_id+-id MODULUS ~

/* id after [read one up] */
aritm+*id    ::= aritm+* _INT_VAL_ ~
aritm+*id    ::= aritm+* _ID_VAL_ ~

/* mul div mod after id [read one up] */
aritm+*      ::= aritm+*id MULTIPLICATION ~
aritm+*      ::= aritm+*id DIVISION ~
aritm+*      ::= aritm+*id MODULUS ~

/* comes back after sequence of mul div mod */
aritm_id     ::= aritm+*id ADD |
aritm_id     ::= aritm+*id SUB |

/* REMOVING NON LAYERED ARITM */

/*
 * semicolon, comma - is not part of aritmethic
 * so we pop aritmethic of the stack and let other
 * rules handle next steps
 */

/* exmp.: 1 */
POP          ::= aritm_id SEMICOLON /
POP          ::= aritm_id COMMA /

/* exmp.: 1 + 1 */
POP          ::= aritm_id+-id SEMICOLON /
POP          ::= aritm_id+-id COMMA /

/* exmp.: 1 + 1 * 1 */
POP          ::= aritm+*id SEMICOLON /
POP          ::= aritm+*id COMMA /

/*
 * EOF ARITHMETIC
 */

/*
 * VARIABLE DECLARATION
 */

/* dont use after INIT_STATE */
var_dec      ::= VAR_DEC_BLK INT +
var_dec      ::= VAR_DEC_BLK CHAR +
var_dec      ::= VAR_DEC_BLK _ID_VAL_ +

var_id       ::= var_dec _ID_VAL_ ~
var_dec      ::= var_id COMMA ~

aritm        ::= var_id EQUALITY +

POP          ::= var_id SEMICOLON -

/* variable useage */
var_use=     ::= id_useage EQUALITY |
aritm        ::= var_use= EQUALITY +
POP          ::= var_use= SEMICOLON -

/* what goes after variable declaration */
POP          ::= VAR_DEC_BLK MAIN /
POP          ::= VAR_DEC_BLK STRUCT_DEC /
POP          ::= VAR_DEC_BLK FOR_DEC /
POP          ::= VAR_DEC_BLK WHILE_DEC /
POP          ::= VAR_DEC_BLK PRINTF_DEC /
POP          ::= VAR_DEC_BLK SCANF /
POP          ::= VAR_DEC_BLK IF_DEC /
POP          ::= VAR_DEC_BLK RETURN /
POP          ::= VAR_DEC_BLK _ID_VAL_ /
POP          ::= VAR_DEC_BLK END /

/* struct */

/* declaration */
struct       ::= INIT_STATE STRUCT_DEC +
strct_name   ::= struct _ID_VAL_ ~
strct_name{  ::= strct_name BEGIN |
VAR_DEC_BLK  ::= strct_name{ BEGIN +
struct{}     ::= strct_name{ END ~
POP          ::= struct{} SEMICOLON -

/* useage */
struct_dot   ::= id_useage DOT ~
struct_attr  ::= struct_dot _ID_VAL_ ~

struct_dot   ::= struct_attr DOT ~

struct_attr= ::= struct_attr  EQUALITY |
aritm        ::= struct_attr= EQUALITY +

POP          ::= struct_attr= SEMICOLON -

/* function */
function_name     ::= INT _ID_VAL_ ~
function_name     ::= CHAR _ID_VAL_ ~
function_name     ::= VOID _ID_VAL_ ~
function_name_(   ::= function_name OPEN_BRACE ~
function_()       ::= function_name_( CLOSE_BRACE ~
function_()_{     ::= function_() BEGIN |
code_blk          ::= function_()_{ BEGIN +
POP               ::= function_()_{ END -


/* main */
main_i       ::= INT MAIN ~
main_(       ::= main_i OPEN_BRACE ~
main_()      ::= main_( CLOSE_BRACE ~
main_(){     ::= main_() BEGIN |
code_blk     ::= main_(){ BEGIN +
POP          ::= main_(){ END -

/* return */
return       ::= code_blk RETURN +
return_int   ::= return _INT_VAL_ ~
POP          ::= return_int SEMICOLON -

/* if () */
if           ::= code_blk IF_DEC +
if_(         ::= if OPEN_BRACE |
bool         ::= if_( OPEN_BRACE +

if_()        ::= if_( CLOSE_BRACE ~
if(){        ::= if_() BEGIN |
code_blk     ::= if(){ BEGIN +
if(){}       ::= if(){ END ~


/* if () {} else */
if_else      ::= if(){} ELSE ~
if_else{     ::= if_else BEGIN |
code_blk     ::= if_else{ BEGIN +
POP          ::= if_else{ END -

/* if () {} else if */
if           ::= if_else IF_DEC ~

/* if () {} and not else */
POP          ::= if(){} STRUCT_DEC /
POP          ::= if(){} INT /
POP          ::= if(){} CHAR /
POP          ::= if(){} FOR_DEC /
POP          ::= if(){} WHILE_DEC /
POP          ::= if(){} PRINTF_DEC /
POP          ::= if(){} SCANF /
POP          ::= if(){} IF_DEC /
POP          ::= if(){} RETURN /
POP          ::= if(){} END /

/* while () {} */

while        ::= code_blk WHILE_DEC +
while(       ::= while OPEN_BRACE ~
while(true   ::= while( TRUE ~
while(true)  ::= while(true CLOSE_BRACE ~

while(){     ::= while(true) BEGIN |
code_blk     ::= while(){ BEGIN +
POP          ::= while(){ END -

/* printf */
printf_      ::= code_blk PRINTF_DEC +
printf_(     ::= printf_ OPEN_BRACE ~

/* printf("string") */
printf_(str  ::= printf_( _STR_VAL_ ~
printf_()    ::= printf_(str CLOSE_BRACE ~

/* printf(variable) */
printf_(var  ::= printf_( _ID_VAL_ ~
printf_()    ::= printf_(var CLOSE_BRACE ~

POP          ::= printf_() SEMICOLON -

/* scanf */
scanf_       ::= code_blk SCANF +
scanf_(      ::= scanf_ OPEN_BRACE ~
scanf_(var   ::= scanf_( _ID_VAL_ ~
scanf_(var)  ::= scanf_(var CLOSE_BRACE ~
POP          ::= scanf_(var) SEMICOLON -
