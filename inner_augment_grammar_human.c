/* no structures at the moment */
#include "inner_lang_values.h"

/* Stack operation
 * + is push
 * - is pop
 * ~ is reduction (top becomes)
 */

/*
new_state       stack_top  token      action
*/
INIT_STATE  ::= INIT_STATE INIT_STATE ~
INT         ::= INIT_STATE INT        +

main_i      ::= INT MAIN ~
main_(      ::= main_i OPEN_BRACE ~
main_)      ::= main_( CLOSE_BRACE ~
code_blk    ::= main_) BEGIN ~
POP         ::= code_blk END -

/* return after main() { */
main_ret    ::= code_blk RETURN +
return_int  ::= main_ret _INT__VAL ~
POP         ::= return_int SEMICOLON -

/* variable declaration after main() { */
var_dec0    ::= code_blk INT +
var_dec0    ::= code_blk CHAR +

var_id      ::= var_dec0 _ID___VAL ~

var_id=     ::= var_id EQUALITY ~

var_id=val  ::= var_id= _INT__VAL ~
var_id=val  ::= var_id= _CHAR_VAL ~

/* remember to check after changing var_decN value */
POP         ::= var_id SEMICOLON -
POP         ::= var_id=val SEMICOLON -

