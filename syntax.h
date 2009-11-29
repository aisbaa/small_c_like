#ifndef SMALL_C_LIKE_SYNTAX
#define SMALL_C_LIKE_SYNTAX

#include <fstream>
#include <map>
#include <vector>

#include "textstream.h"

using namespace std;

typedef struct {
  int newState;
  int state;
  int term;
  int action;
} MatrixValues;

typedef vector<MatrixValues> Matrix;
typedef vector<MatrixValues>::iterator MatrixIterator;

const string action_pop_str = "-";
const string action_push_str = "+";
const string action_reduction_str = "~";
const string action_reduction_check_str = "|";

const int action_pop = 0;
const int action_push = 1;
const int action_reduction = 2;
const int action_reduction_check = 3;

class Syntax {

 private:  
  TextStream * stream;
  ifstream   * file;

  Matrix matrix;
  MatrixIterator it;

  void parseFile();
  void fillMatrix();

  int makeNumber();
  int makeAction();
  int convertToInteger(string);

  bool isNumber(string);

  int getActionNumber(char);

  MatrixValues findMatrix(int, int);

 public:
  Syntax(string);

  void printMatrix();

  int getNewState(int, int);
  /**
   * returns action
   *   reduction
   *   push
   *   pop
   */
  int getNextState(int prev_state, int token, int * new_state);
};

const int err_invalid_action_inaugmented_grammar = 0;

#endif
