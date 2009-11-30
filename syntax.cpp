#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "syntax.h"
#include "textstream.h"

using namespace std;

Syntax::Syntax(string fileName) {
  this->file   = new ifstream(fileName.c_str(), ios_base::in);
  this->stream = new TextStream(file);

  try {
    while (this->file->good()) {
      fillMatrix();
    }
  } catch (int err) {
    if (err != STREAM_IS_NOT_GOOD_FOR_READING) throw ;
  }

  printMatrix();
  //  getNextState(3, 1, NULL);
}

int Syntax::makeNumber() {
  string number, value;

  while (this->file->good() && !isNumber(value) && value != "0") {
    value = this->stream->getNextEntity();
    number += value;
  }

  return convertToInteger(number);
}

int Syntax::makeAction() {
  string action = this->stream->getNextEntity();

  if (action == action_pop_str) return action_pop;
  if (action == action_pop_check_str) return action_pop_check;

  if (action == action_push_str) return action_push;
  if (action == action_push_check_str) return action_push_check;

  if (action == action_reduction_str) return action_reduction;
  if (action == action_reduction_check_str) return action_reduction_check;

  throw err_invalid_action_inaugmented_grammar;

  return 0; // gets ride of warnning
}

void Syntax::fillMatrix() {
  MatrixValues newRecord;

  newRecord.newState = makeNumber();
  newRecord.state    = makeNumber();
  newRecord.term     = makeNumber();
  newRecord.action   = makeAction();
    
  this->matrix.push_back(newRecord);
}

bool Syntax::isNumber(string value) {
  if (atoi(value.c_str()))
    return true;
  return false;
}

int Syntax::convertToInteger(string value) {
  if (atoi(value.c_str()))
    return atoi(value.c_str());
  return NULL;
}

MatrixValues Syntax::findMatrix(int state, int term) {
  for (this->it = this->matrix.begin(); this->it < this->matrix.end(); this->it++) {
    MatrixValues matrix = *(this->it);
    if (matrix.state == state && matrix.term == term)
      return matrix;
  }

  // cout << " -- nothing found -- " << endl;
  // should throw exception
}

int Syntax::getActionNumber(char action) {
  if (action == '-')
    return action_pop;
  if (action == '+')
    return action_push;
  if (action == '~')
    return action_reduction;
  return NULL;
}

/*
 * PUBLIC
 */

void Syntax::printMatrix() {
  for (this->it = this->matrix.begin(); this->it < this->matrix.end(); this->it++) {
    MatrixValues a = *(this->it);
    cout.width(4);
    cout << a.newState << " ::= ";

    cout.width(4);
    cout << a.state << " ";

    cout.width(4);
    cout << a.term
         << " "
         << a.action
         << endl;
  }
}
/*
int Syntax::getNewState(int prev_state, int token) {
  MatrixValues matrix = findMatrix(prev_state, token);
  return matrix.state;
}
*/
int Syntax::getNextState(int prev_state, int token, int * new_state) {
  MatrixValues matrix;

  matrix = findMatrix(prev_state, token);
    
  *new_state = matrix.newState;

  return matrix.action;
}
