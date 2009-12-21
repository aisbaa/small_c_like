#include "inner_lang_values.h"
#include "inner_augment_grammar_states.h"

/* I got to beginnig of main function, I just outup string */
/* poping of the stack:       {          )          (          )          main       int */
main_op_cl_be OUTPUT_SIGNLE 5 DONT_CHECK DONT_CHECK DONT_CHECK DONT_CHECK DONT_CHECK DONT_CHECK
MAIN_FUNCT:
DONT_PUSH DONT_PUSH DONT_PUSH

/* closing brace } after int_main(){ */
main_op_cl_be_en OUTPUT_SIGNLE 1 DONT_CHECK
END_OF_FUNCT:
DONT_PUSH_S DONT_PUSH DONT_PUSH

/**
 * FUNCTTION
 */

/* function declaration */
function_name OUTPUT_SIGNLE 2 DONT_CHECK DONT_CHECK
glob_funct $0
DONT_PUSH DONT_PUSH DONT_PUSH

/* function parameter */
func_id OUTPUT_SIGNLE 2 DONT_CHECK DONT_CHECK
fparam $0 $1
DONT_PUSH DONT_PUSH DONT_PUSH

/*end of function declaration */
function_end OUTPUT_SIGNLE 2 DONT_CHECK DONT_CHECK
func_end
DONT_PUSH DONT_PUSH DONT_PUSH

/**
 * VARIABLE DECLARATION
 */
/* var registration, exmp.: int a */
var_id REGISTRATE_SINGLE 2 DONT_CHECK DONT_CHECK
VAR_DEC $0 $1
$0 _INT_VAL_ _INT_VAL_

//                           aritm      =          id
var_init_val OUTPUT_SIGNLE 3 _INIT_VAL_ DONT_CHECK _INIT_VAL_
= , , $0 , $2
DONT_PUSH_SC DONT_PUSH DONT_PUSH

/**
 * ARITMETHIC
 */
//                           , or ;     number or variable that holds number
aritm_single PUSH_TO_STACK 2 DONT_CHECK _INT_VAL_
DONT_OUTPUT
$1 _INT_VAL_ _INT_VAL_

/**
 * RETURN
 */
//                               aritm     return
return_semicolon OUTPUT_SIGNLE 2 _INT_VAL_ RETURN
ret $0
DONT_PUSH DONT_PUSH DONT_PUSH
