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
  bool repeat;
  do {
    repeat = false;

    cout << ">> ";

    try {
      action = this -> syntax -> getNextState(
                                              this -> stateStack.top(),
                                              token -> getInnerLang(),
                                              &new_state
                                              );
    } catch (int err) {
      this -> gotError = true;
      cout << "got error" << endl;
      // TODO
      // this means that state was not found
    }

    cout << *token << " action " << action << " ";

    switch (action) {
    case action_pop:
      cout << "pop  " << this -> stateStack.top();
      this -> stateStack.pop();
      break;

    case action_push:
      cout << "push " << new_state;
      this -> stateStack.push(new_state);
      break;

    case action_reduction:
      cout << "rdct " << new_state;
      this -> stateStack.top() = new_state;
      break;

    case action_reduction_check:
      cout << "chck " << new_state;
      this -> stateStack.top() = new_state;
      repeat = true;
      break;

    default:
      cout << "didnt found";
      this -> gotError = true;
    }

    cout << endl;

  } while(repeat);

  if (this -> semantic != NULL)
    /* give token to semantic */
    ;
  else
    delete token;

}

bool Analizer::complete() {
  if (this -> gotError)
    return false;

  return (
          this -> stateStack.size() == 1 &&
          this -> stateStack.top() == INIT_STATE &&
          !this -> gotError
          );
}
