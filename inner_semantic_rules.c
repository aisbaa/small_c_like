#include "inner_lang_values.h"
#include "inner_augment_grammar_states.h"

/* I got to beginnig of main function, I just outup string */
/* poping of the stack:       {    )     (          )          main       int */
main_op_cl_be OUTPUT_SIGNLE 5 DONT_CHECK DONT_CHECK DONT_CHECK DONT_CHECK DONT_CHECK
MAIN_LABEL:
DONT_PUSH DONT_PUSH DONT_PUSH

/* dviejų skaičių sudėtis */

/* po kurių eina sudėtis 
aritm_id+-id+- 3 _INT_VAL_ _ARITM_+-_SIGN_ _INT_VAL_
$1, $2, $0, $@
$@ _ID_VAL_ _INT_VAL_
*/
/* po kurių eina skyrybos ženklas 
aritm_id_pm_id_eof 4 _END_OF_ARITMETHIC_ _INT_VAL_ _ARITM_PM_SIGN_ _INT_VAL_
$3, $2, $1, $@
$@ _ID_VAL_ _INT_VAL_
*/
