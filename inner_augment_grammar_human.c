# no structure at the moment
#include "inner_lang_values.h"

$           ::= $

$           ::= CHAR

$           ::= INT

INT         ::= MAIN

main_i      ::= INT MAIN
main_(      ::= main_i OPEN_BRACE
main_)      ::= main_( CLOSE_BRACE
main_{      ::= main_) BEGIN
main        ::= main_{ END

POP         ::= main

#
# return after main
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

# program
program               ::= program_fornt program_main program_body
program_fornt         ::= declaration
program_main          ::= int main empty_braces
program_body          ::= { code_block }

# declaration
declaration           ::= function_declaration

declaration           ::= struct_schedule


function_declaration  ::= data_type function_name ( ) { function_body } ;
delaration
function_declaration  ::= data_type function_name ( parameter_list_declaration ) { function_body } ;


function_call         ::= function_name ( ) ;

function_call         ::= function_name ( parameter_list ) ;


function_name         ::= word

function_body         ::= code_block


code_block            ::= simple_code_block

code_block            ::= return


simple_code_block     ::= variable_declaration

simple_code_block     ::= variable_assignment

simple_code_block     ::= function_call

simple_code_block     ::= while

simple_code_block     ::= for

simple_code_block     ::= if

simple_code_block     ::= array_assign


output_declaration    ::= printf printf_body ;
printf_body           ::= ( output_data )


output_data           ::= string

output_data           ::= variable_name

output_data           ::= mixed


out_content           ::= variable_name

out_content           ::= string


mixed_pre             ::= out_content +
mixed                 ::= mixed_pre output_data


input_declaration     ::= variable_name = "scanf(" natral_number ");"


if                    ::= "if (" condition ")" "{" code_block "}" [ else_declaration ]
else_declaration      ::= else_if | else
else_if               ::= "else" if
else                  ::= "else {" code_block "}"


condition             ::= bool_value | comparison | logic_operation
logic_operation       ::= bool_value logical_operator bool_value
comparison            ::= comparable comparison_operator comparable
comparable            ::= variable_name | digit | string | arithmetic_expression

<comparison_operator>   ::= "==" | "!=" | ">" | "<" | "<=" | ">="
<logical_operator>      ::= "&&" | "||"



for                   ::= "for (" for_inside_decl ";" for_inside_test ";" for_inside_action ")" "{" code_block "}"

for_inside_decl       ::= variable_declaration | nothing
for_inside_test       ::= condition
for_inside_action     ::= var_minimal_assignment  | nothing


while                 ::= "while (" condition ")" "{" code_block "}"


struct_schedule       ::= "struct" struct_name "{" struct_body "};"

struct_body           ::= { variable_declaration }

struct_declaration    ::= struct_name variable_name ";"

struct_usage_get_val  ::= variable_name "-" variable_name ";"

struct_usage_set_val  ::= variable_name "-" variable_name "=" struct_assign_value ";"

struct_assign_value   ::= arithmetic_expression | string | char

struct_name           ::= word


array_declaration     ::= data_type array_name "[" natural_number "]" ["=" fill_array_values] ";"

array_usage           ::= array_name "[" array_indicator "]"

array_assign          ::= array_name "[" array_indicator "]" = array_assign_data;

array_assign_data     ::= arithmetic_expression | string

array_indicator       ::= natural_number | variable_name | arithmetic_expression

array_name            ::= word


fill_array_values     ::= numeric_array_fill | char_array_fill

numeric_array_fill    ::= "{" nubmers_in_array "}"

nubmers_in_array      ::= int { "," int }

char_array_fill       ::= string


variable_declaration        ::= data_type variable_single_declaration {"," variable_single_declaration} ";"

variable_single_declaration ::= variable_name [ "=" arithmetic_expression ]

variable_assignment         ::= var_minimal_assignment ";"

var_minimal_assignment      ::= variable_name "=" arithmetic_expression | variable_name "="  string

variable_name               ::= word


arithmetic_expression ::= term | factor composition term
term                  ::= factor | factor multi_div term
factor                ::= int | array_usage | struct_usage_get_val | "(" arithmetic_expression ")" | function_call

composition           ::= add | sub
multi_div             ::= mul | div | mod

add                   ::= "+"
sub                   ::= "-"

mul                   ::= "*"
div                   ::= "/"
mod                   ::= "%"


data_type         ::= "int" | "char" | struct_name

int               ::= "0" | [ "-" ] natural_number

string            ::= '"' {pseudo_ascii} '"'

char              ::= "'" pseudo_ascii "'"

pseudo_ascii      ::= letter_or_digit | special_chars 

letter_or_digit   ::= letter | digit

bool_value        ::= "true" | "false"


return            ::= "return" return_value ) ";"
return_value      ::= arithmetic_expression | variable_name | int


nothing           ::=

parameter_list_delaration ::= parameter_declare {"," parameter_declare}

parameter_declare ::= data_type variable_name

parameter_list    ::= parameter {"," parameter}

parameter         ::= variable_name | arithmetic_expression


natural_number    ::= digit | digit_exclude_zero {digit}

digit             ::= "0" | digit_exclude_zero

digit_exclude_zero::= "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"


word              ::= letter { letter_or_digit }

letter_or_digit   ::= letter | digit

special_chars     ::= "." | "," | ":" | ";" | "!" | "#" | "$" | "%" | "&" | "(" 
		      | ")" | "*" | "+" | "-" | "/" | "@" | "" | "=" | "" | "?"
		      | "[" | "\" | "]" | "^" | "_" | "{" | "}" | "|" | "~" | "'"
		      | """ | " "

letter            ::= "A" | "B" | "C" | "D" | "E" | "F" | "G"
                      | "H" | "I" | "J" | "K" | "L" | "M" | "N"
                      | "O" | "P" | "Q" | "R" | "S" | "T" | "U"
                      | "V" | "W" | "X" | "Y" | "Z" |
                      | "a" | "b" | "c" | "d" | "e" | "f" | "g"
                      | "h" | "i" | "j" | "k" | "l" | "m" | "n"
                      | "o" | "p" | "q" | "r" | "s" | "t" | "u"
                      | "v" | "w" | "x" | "y" | "z"
