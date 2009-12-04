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
   
   main
   variable declaration
   if [ else [if] ]
   return

*/

/* reikia padaryti

   bool statement (reiškiniai kurių atsakymas true arba false)
   masyvai (deklaracija ir panaudojimas)
   f-jos (deklaracija ir panaudojimas)
   scanf printf

   struct (panaudojimas)
   aritmetika

 */


/*
new_state       stack_top  token      action
*/
INIT_STATE  ::= INIT_STATE INIT_STATE ~
INT         ::= INIT_STATE INT        +
INT         ::= INIT_STATE CHAR       +

/* aritmethic */
aritm_id    ::= aritm _INT_VAL_ ~
aritm_id    ::= aritm _ID_VAL_ ~

aritm+-     ::= aritm_id ADD ~
aritm+-     ::= aritm_id SUB ~

aritm+-id   ::= aritm+- _ID_VAL_ ~
aritm+-id   ::= aritm+- _INT_VAL_ ~

aritm+-     ::= aritm+-id ADD ~
aritm+-     ::= aritm+-id SUB ~

/* first comes multiplication */
aritm1*     ::= aritm_id MULTIPLICATION ~
aritm1*     ::= aritm_id DIVISION ~
aritm1*     ::= aritm_id MODULUS ~

aritm1**    ::= aritm1* _INT_VAL_ |
aritm1**    ::= aritm1* _ID_VAL_ |

aritm**     ::= aritm1** _INT_VAL_ +
aritm**     ::= aritm1** _ID_VAL_ +

aritm+-     ::= aritm1** ADD ~
aritm+-     ::= aritm1** SUB ~

/* multiplication after addition */
aritm*      ::= aritm+-id MULTIPLICATION +
aritm*      ::= aritm+-id DIVISION +
aritm*      ::= aritm+-id MODULUS +

aritm**     ::= aritm* _INT_VAL_ ~
aritm**     ::= aritm* _ID_VAL_ ~

aritm*      ::= aritm** MULTIPLICATION ~
aritm*      ::= aritm** DIVISION ~
aritm*      ::= aritm** MODULUS ~

/* pops if after mul div mod goes add sub */
POP         ::= aritm** ADD /
POP         ::= aritm** SUB /

/* pops aritm state */
POP         ::= aritm** SEMICOLON /
POP         ::= aritm1** SEMICOLON /
POP         ::= aritm_id SEMICOLON /
POP         ::= aritm+-id SEMICOLON /

/* variable declaration dont use after INIT_STATE */
var_dec     ::= VAR_DEC_BLK INT +
var_dec     ::= VAR_DEC_BLK CHAR +
var_dec     ::= VAR_DEC_BLK _ID_VAL_ +

var_id      ::= var_dec _ID_VAL_ ~

var_id=     ::= var_id EQUALITY ~

var_id=-    ::= var_id= SUB ~

var_id=val  ::= var_id=- _INT_VAL_ ~
var_id=val  ::= var_id=  _INT_VAL_ ~
var_id=val  ::= var_id=  _CHAR_VAL_ ~

var_dec     ::= var_id COMMA ~
var_dec     ::= var_id=val COMMA ~

POP         ::= var_id SEMICOLON -
POP         ::= var_id=val SEMICOLON -

/* variable useage */
id_useage   ::= code_blk _ID_VAL_ +
var_use=    ::= id_useage EQUALITY |
aritm       ::= var_use= EQUALITY +
POP         ::= var_use= SEMICOLON -

/* what goes after variable declaration */
POP         ::= VAR_DEC_BLK MAIN /
POP         ::= VAR_DEC_BLK STRUCT_DEC /
POP         ::= VAR_DEC_BLK FOR_DEC /
POP         ::= VAR_DEC_BLK WHILE_DEC /
POP         ::= VAR_DEC_BLK PRINTF_DEC /
POP         ::= VAR_DEC_BLK SCANF_DEC /
POP         ::= VAR_DEC_BLK IF_DEC /
POP         ::= VAR_DEC_BLK RETURN /
POP         ::= VAR_DEC_BLK _ID_VAL_ /
POP         ::= VAR_DEC_BLK END /

/* code block */
VAR_DEC_BLK ::= code_blk INT *
VAR_DEC_BLK ::= code_blk CHAR *

/* after code block */
POP         ::= code_blk END /

/* struct */
struct      ::= INIT_STATE STRUCT_DEC +
strct_name  ::= struct _ID_VAL_ ~
strct_name{ ::= strct_name BEGIN |
VAR_DEC_BLK ::= strct_name{ BEGIN +
struct{}    ::= strct_name{ END ~
POP         ::= struct{} SEMICOLON -

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
if(){       ::= if_(bool) BEGIN |
code_blk    ::= if(){ BEGIN +
if(){}      ::= if(){ END ~


/* if () {} else */
if_else     ::= if(){} ELSE ~
if_else{    ::= if_else BEGIN |
code_blk    ::= if_else{ BEGIN +
POP         ::= if_else{ END -

/* if () {} else if */
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
