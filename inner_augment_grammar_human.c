#include "inner_lang_values.h"

/**
 * Stack operation
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
   
   arithmetic
   boolean arithmetic
   variable declaration

   struct
   main
   if [ else [if] ]
   return
   scanf
   printf

   f-jos (deklaracija su parametrais, panaudojimas)
*/

/* reikia padaryti

   masyvai (deklaracija ir panaudojimas)
   f-jos (deklaracija ir panaudojimas)
   scanf printf

 */


/*
new_state       stack_top  token      action
*/
INIT_STATE   ::= INIT_STATE INIT_STATE ~
INT          ::= INIT_STATE INT        +
CHAR         ::= INIT_STATE CHAR       +
VOID         ::= INIT_STATE VOID       +

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

/* LAYERED BOOL ARITMETHIC */
boollayer    ::= bool OPEN_BRACE |
boollayer    ::= bool_val_op OPEN_BRACE |

bool         ::= boollayer OPEN_BRACE +
/* reduction after bool layer */
bool_val     ::= boollayer CLOSE_BRACE ~

/* NON LAYERED BOOL ARITMETHIC */
/* direct (constants) */
bool_val     ::= bool TRUE ~
bool_val     ::= bool FALSE ~

bool_val_op  ::= bool_val OR ~
bool_val_op  ::= bool_val AND ~

bool_val     ::= bool_val_op TRUE ~
bool_val     ::= bool_val_op FALSE ~

/* indirect (variables) */
bool_id      ::= bool _ID_VAL_ ~  // this might be not bool id, so this has three ways to go
bool_val     ::= bool_val_op _ID_VAL_ ~ // this must be bool id

/* indirect - id turns out to be bool type */
bool_val_op  ::= bool_id AND ~
bool_val_op  ::= bool_id OR ~

/* what goes after liniar bool arithmetic */
POP          ::= bool_val CLOSE_BRACE /
POP          ::= bool_id  CLOSE_BRACE / // must be boolean variable
POP          ::= bool_id==id CLOSE_BRACE /
POP          ::= bool_id==exp CLOSE_BRACE /

/* TRADITIONAL ARITHMETIC INSIDE BOOL ARITHMETIC */

/* first comes int */
bool_int     ::= bool _INT_VAL_ |
aritm        ::= bool_int _INT_VAL_ *

/* turns out that id is numerical */
/* indirect - id turns out to be numerical type */
bool_int+    ::= bool_id ADD |
bool_int+    ::= bool_id SUB |

bool_int+    ::= bool_id MULTIPLICATION |
bool_int+    ::= bool_id DIVISION |
bool_int+    ::= bool_id MODULUS |

aritm_id     ::= bool_int+ ADD *
bool_int+    ::= bool_int+ SUB *

bool_int+    ::= bool_int+ MULTIPLICATION *
bool_int+    ::= bool_int+ DIVISION *
bool_int+    ::= bool_int+ MODULUS *

/* stand alone id turns out to be comperable */
bool_id==    ::= bool_id IS_EQUAL_TO ~
bool_id==    ::= bool_id NOT_EQUAL_TO ~

bool_id==    ::= bool_id GREATER_OR_EQUAL ~
bool_id==    ::= bool_id LESS_OR_EQUAL ~

bool_id==    ::= bool_id GREATER ~
bool_id==    ::= bool_id LESS ~

bool_id==id  ::= bool_id== _ID_VAL_ ~

  /* and what if we are geting some operation after bool_id==id */

bool_id==exp ::= bool_id==id ADD |
bool_id==exp ::= bool_id==id SUB |

bool_id==exp ::= bool_id==id MULTIPLICATION |
bool_id==exp ::= bool_id==id DIVISION |
bool_id==exp ::= bool_id==id MODULUS |

aritm_id     ::= bool_id==exp ADD *
aritm_id     ::= bool_id==exp SUB *

aritm_id     ::= bool_id==exp MULTIPLICATION *
aritm_id     ::= bool_id==exp DIVISION *
aritm_id     ::= bool_id==exp MODULUS *

/* after aritm which started with id + sign goes */
bool_int==   ::= bool_int+ IS_EQUAL_TO |
bool_int==   ::= bool_int+ NOT_EQUAL_TO |

bool_int==   ::= bool_int+ GREATER_OR_EQUAL |
bool_int==   ::= bool_int+ LESS_OR_EQUAL |

bool_int==   ::= bool_int+ GREATER |
bool_int==   ::= bool_int+ LESS |

/* after aritm that started with numerical goes */
bool_int==   ::= bool_int IS_EQUAL_TO |
bool_int==   ::= bool_int NOT_EQUAL_TO |

bool_int==   ::= bool_int GREATER_OR_EQUAL |
bool_int==   ::= bool_int LESS_OR_EQUAL |

bool_int==   ::= bool_int GREATER |
bool_int==   ::= bool_int LESS |

/* after */
aritm        ::= bool_int== IS_EQUAL_TO +
aritm        ::= bool_int== NOT_EQUAL_TO +

aritm        ::= bool_int== GREATER_OR_EQUAL +
aritm        ::= bool_int== LESS_OR_EQUAL +

aritm        ::= bool_int== GREATER +
aritm        ::= bool_int== LESS +

bool_val     ::= bool_int== CLOSE_BRACE |

/* string == string */
bool_str     ::= bool _STR_VAL_ ~

bool_str==   ::= bool_str IS_EQUAL_TO ~
bool_str==   ::= bool_str NOT_EQUAL_TO ~

bool_str==   ::= bool_str GREATER_OR_EQUAL ~
bool_str==   ::= bool_str LESS_OR_EQUAL ~

bool_str==   ::= bool_str GREATER ~
bool_str==   ::= bool_str LESS ~

bool_s==s    ::= bool_str== _STR_VAL_ ~

POP          ::= bool_s==s CLOSE_BRACE /

/* char == char */
bool_chr     ::= bool _CHAR_VAL_ ~

bool_chr==   ::= bool_chr IS_EQUAL_TO ~
bool_chr==   ::= bool_chr NOT_EQUAL_TO ~

bool_chr==   ::= bool_chr GREATER_OR_EQUAL ~
bool_chr==   ::= bool_chr LESS_OR_EQUAL ~

bool_chr==   ::= bool_chr GREATER ~
bool_chr==   ::= bool_chr LESS ~

bool_c==c    ::= bool_chr== _CHAR_VAL_ ~

POP          ::= bool_c==c CLOSE_BRACE /

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

POP          ::= aritm_id IS_EQUAL_TO /
POP          ::= aritm_id NOT_EQUAL_TO /
POP          ::= aritm_id GREATER_OR_EQUAL /
POP          ::= aritm_id LESS_OR_EQUAL /

POP          ::= aritm_id GREATER /
POP          ::= aritm_id LESS /

/* exmp.: 1 + 1 */
POP          ::= aritm_id+-id SEMICOLON /
POP          ::= aritm_id+-id COMMA /

POP          ::= aritm_id+-id IS_EQUAL_TO /
POP          ::= aritm_id+-id NOT_EQUAL_TO /
POP          ::= aritm_id+-id GREATER_OR_EQUAL /
POP          ::= aritm_id+-id LESS_OR_EQUAL /

POP          ::= aritm_id+-id GREATER /
POP          ::= aritm_id+-id LESS /

/* exmp.: 1 + 1 * 1 */
POP          ::= aritm+*id SEMICOLON /
POP          ::= aritm+*id COMMA /

POP          ::= aritm+*id IS_EQUAL_TO /
POP          ::= aritm+*id NOT_EQUAL_TO /
POP          ::= aritm+*id GREATER_OR_EQUAL /
POP          ::= aritm+*id LESS_OR_EQUAL /

POP          ::= aritm+*id GREATER /
POP          ::= aritm+*id LESS /

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

/* array */
/* su char ir int vienodai */
arr_dec      ::= var_id SQUARE_BRACKET_OPEN ~
arr_dec      ::= arr_dec _INT_VAL_ ~
arr_dec      ::= arr_dec SQUARE_BRACKET_CLOSE ~
POP          ::= arr_dec SEMICOLON -

array        ::= arr_dec EQUALITY +
array_int    ::= array EQUALITY +

POP      ::= array _CHAR_VAL_ -
POP      ::= array _STR_VAL_ -
POP      ::= array _INT_VAL_ -

array_int      ::= array BEGIN ~
array_int_val  ::= array_int _INT_VAL_ ~
array_int_val  ::= array_int_val COMMA ~
array_int_val  ::= array_int_val _INT_VAL_ ~
POP  ::= array_int_val END -
/* pobaiga */


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
function_name_(var ::= function_name_( INT |
function_name_(var ::= function_name_( CHAR |
func_param        ::= function_name_(var INT +
func_param        ::= function_name_(var CHAR +

function_name_() ::= function_name_( CLOSE_BRACE ~

function_name_(){ ::= function_name_(var BEGIN |
function_name_(){ ::= function_name_() BEGIN |
code_blk          ::= function_name_(){ BEGIN +
POP               ::= function_name_(){ END -
/* function parameters */
func_param ::= func_param INT ~
func_param ::= func_param CHAR ~
func_id     ::= func_param _ID_VAL_ ~

func_id,    ::= func_id COMMA ~

func_id,id  ::= func_id, INT ~
func_id,id  ::= func_id, CHAR ~
func_id,id  ::= func_id,id _ID_VAL_ ~

func_id,    ::= func_id,id COMMA ~

POP          ::= func_id CLOSE_BRACE -
POP          ::= func_id,id CLOSE_BRACE -
/* end */

/* function call */
func_call    ::= id_useage OPEN_BRACE ~
func_attr    ::= func_call _ID_VAL_ ~
func_attr    ::= func_attr COMMA ~
func_attr    ::= func_attr _ID_VAL_ ~

func_call()  ::= func_attr CLOSE_BRACE ~
func_call()  ::= func_call CLOSE_BRACE ~

POP          ::= func_call() SEMICOLON -


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
while(       ::= while OPEN_BRACE |
bool         ::= while( OPEN_BRACE +
while()      ::= while( CLOSE_BRACE ~

while(){     ::= while() BEGIN |
code_blk     ::= while(){ BEGIN +
POP          ::= while(){ END -


/* printf(a + "a" + b + "b") */
printf_      ::= code_blk PRINTF_DEC +
printf_(     ::= printf_ OPEN_BRACE |
multi_pr     ::= printf_( OPEN_BRACE +
printf_()    ::= printf_( CLOSE_BRACE ~
POP          ::= printf_() SEMICOLON -

multi_id     ::= multi_pr _STR_VAL_ ~
multi_id     ::= multi_pr _ID_VAL_ ~
multi_id     ::= multi_pr _CHAR_VAL_ ~

multi_id+    ::= multi_id ADD ~

multi_id+id  ::= multi_id+ _ID_VAL_ ~
multi_id+id  ::= multi_id+ _STR_VAL_ ~
multi_id+id  ::= multi_id+ _CHAR_VAL_ ~

multi_id+    ::= multi_id+id ADD ~

POP          ::= multi_id CLOSE_BRACE /
POP          ::= multi_id+id CLOSE_BRACE /


/* scanf(var) */
scanf_       ::= code_blk SCANF +
scanf_(      ::= scanf_ OPEN_BRACE ~
scanf_(var   ::= scanf_( _ID_VAL_ ~
scanf_(var)  ::= scanf_(var CLOSE_BRACE ~
POP          ::= scanf_(var) SEMICOLON -
