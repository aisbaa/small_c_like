# no structure at the moment
#include "inner_lang_values.h"

$           ::= $
            ::= $ INT
INT         ::= MAIN

main_i      ::= INT MAIN
main_(      ::= main_i OPEN_BRACE
main_)      ::= main_( CLOSE_BRACE
main_{      ::= main_) BEGIN
main        ::= main_{ END

POP         ::= main

#
# return after main() {
#

return      ::= main_{ RETURN
return_int  ::= return INT
return_end  ::= return_int SEMICOLON

POP         :: return_end

#
# variable declaration after main() {
#
var_dec0    ::= main_{ INT
var_dec0    ::= main_{ CHAR

var_id      ::= var_dec0 ID
var_id      ::= var_dec0 ID

var_id=     ::= var_id EQUALITY

var_id=val  ::= var_id INT_VAL
var_id=val  ::= var_id CHAR_VAL

# remember to check after changing var_decN value
var_decl    ::= var_id SEMICOLON
var_decl    ::= var_id=val SEMICOLON

POP         ::= var_decl
