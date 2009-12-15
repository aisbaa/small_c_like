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
DONT_PUSH DONT_PUSH DONT_PUSH

/*
 * var registration, exmp.: int a
 */

/* starting registration queue */
var_dec_i REGISTRATE_START 1 DONT_CHECK
int $0
$0 INT _INT_VAL_

/* var registration, exmp.: a after int 
var_id REGISTRATE_SINGLE 1 _ID_VAL_
DONT_OUTPUT
*/
