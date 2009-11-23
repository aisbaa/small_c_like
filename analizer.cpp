#include <stack>

#include "inner_lang_values.h"
#include "syntax.h"
#include "token.h"

#include "analizer.h"

Analizer::Analizer(Syntax * syntax, void * semantic) {
  if (syntax == NULL) throw "Analizer can't check without Syntax object.";
  this -> syntax = syntax;

  this -> semantic = semantic;

  this -> gotError = false;
  this -> stateStack.push(INIT_STATE);
}

void Analizer::check(Token * token) {
  int new_state;
  int action;

  try {
    action = this -> syntax -> getNextState(
                                            this -> stateStack.top(),
                                            token -> getInnerLang(),
                                            &new_state
                                            );
  } catch (...) {
    this -> gotError = true;
    // this means that state was not found
    // TODO
  }

  switch (action) {
  case action_pop:
    this -> stateStack.pop();
    break;

  case action_push:
    this -> stateStack.push(new_state);
    break;

  case action_reduction:
    this -> stateStack.top() = new_state;
    break;
  }

  if (this -> semantic != NULL)
    /* give token to semantic */
    ;
  else {
    cout << token << endl; // gues token brought in iostream
    delete token;
  }
}

bool Analizer::complete() {
  if (this -> gotError)
    return false;

  return this -> stateStack.size() == 1;
}
