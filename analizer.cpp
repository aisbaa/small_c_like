#include <stack>
#include <vector>

#include "inner_lang_values.h"
#include "syntax.h"
#include "token.h"

#include "analizer.h"

Analizer::Analizer(Syntax * syntax, void * semantic, InnerLang * lang) {
  if (syntax == NULL) throw "Analizer can't check without Syntax object.";
  this -> syntax = syntax;

  this -> semantic = semantic;
  this -> lang = lang;

  this -> gotError = false;
  this -> stateStack.push(INIT_STATE);
}

void Analizer::check(Token * token) {
  int new_state;
  int action;

  bool repeat;
  bool skipErr = false;;

  do {
    action = -1;
    repeat = false;

    try {
      action = this -> syntax -> getNextState(
                                              this -> stateStack.top(),
                                              token -> getInnerLang(),
                                              &new_state
                                              );
    } catch (UnexpectedTokenException unexp) {
      this -> gotError = true;

      if (!skipErr) {
        skipErr = true; 
        cerr << "syntax error with : "
             << token -> getSourceText() << endl;

        if (this -> lang != NULL) {
          vector<int> expects = this -> syntax -> getTokensWithState(this -> stateStack.top());
          cerr << "expected one of: ";

          for (
               vector<int>::iterator it = expects.begin();
               it != expects.end();
               it++
               )
            cerr << this -> lang -> getOuterLangValue(*it) << ", ";
          cerr << endl;
        }
      }
    }

    if (!skipErr)
      cout << ">>" << *token << " action " << action;
    
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

    case action_pop_check:
      cout << "popc " << this -> stateStack.top();
      this -> stateStack.pop();
      repeat = true;
      break;

    case action_push_check:
      cout << "pshc " << new_state;
      this -> stateStack.push(new_state);
      repeat = true;
      break;

    case action_reduction_check:
      cout << "rdtc " << new_state;
      this -> stateStack.top() = new_state;
      repeat = true;
      break;
    }

    if (!skipErr)
      cout << " curr state: "
           << this -> stateStack.top()
           << endl;
    else
      skipErr = false;

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
