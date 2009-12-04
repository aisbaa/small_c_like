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

/**
 * action assigners
 */
const string action_pop_str = "-";
const string action_pop_check_str = "/";
const string action_push_str = "+";
const string action_push_check_str = "*";
const string action_reduction_str = "~";
const string action_reduction_check_str = "|";

/**
 * action values
 */
const int action_pop = 0;
const int action_pop_check = 1;
const int action_push = 2;
const int action_push_check = 3;
const int action_reduction = 4;
const int action_reduction_check = 5;

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

#include <stdexcept>

class UnexpectedTokenException : public logic_error {
public:
   explicit UnexpectedTokenException(const string err) : logic_error(err) {}
};

class InvalidActionInaugmentedGrammar : public logic_error {
public:
   explicit InvalidActionInaugmentedGrammar(const string err) : logic_error(err) {}
};

#endif
