#include <stack>
#include <vector>

//#include "inner_lang_values.h"

#include "semantic.h"
#include "syntax.h"
#include "token.h"

#include "analizer.h"

Analizer::Analizer(Syntax * syntax, Semantic * semantic, InnerLang * lang) {
  if (syntax == NULL) throw "Analizer can't check without Syntax object.";
  this -> syntax = syntax;

  this -> semantic = semantic;
  this -> lang = lang;

  this -> gotError = false;
  this -> syntaxStack.push(INIT_STATE);
}

Analizer::~Analizer() {
  while (!this -> semanticStack.empty()) {
    delete this -> semanticStack.top();
    this -> semanticStack.pop();
  }
}

bool Analizer::syntaxStackOperation(int action, int new_state) {
  switch (action) {
  case action_pop:
  case action_pop_check:
    this -> syntaxStack.pop();
    break;

  case action_push:
  case action_push_check:
    this -> syntaxStack.push(new_state);
    break;

  case action_reduction:
  case action_reduction_check:
    this -> syntaxStack.top() = new_state;
    break;
  }

  if (action == action_push_check || action == action_pop_check || action == action_reduction_check)
    return true;

  return false;
}

void Analizer::semanticStackOperation(int state) {
  const SemanticRule * rule = this -> semantic -> getSemanticRule(state);
  if (rule == NULL) return;

  vector<Token *> worksWith;
  for (unsigned int pops = 0; pops < rule -> stackSize; pops++) {
    worksWith.push_back(this -> semanticStack.top());
    this -> semanticStack.pop();
  }

  this -> output << "I'm working on this." << endl;
}

/*
 * PUBLIC
 */

string Analizer::check(Token * token) {
  this -> semanticStack.push(token);

  bool repeat;
  string analysisInfo;

  do {
    int action = -1;
    int new_state;

    try {
      action = this -> syntax -> getNextState(this -> syntaxStack.top(), token -> getInnerLang(), &new_state);
    } catch (UnexpectedTokenException unexp) {
      this -> gotError = true;
      throw UnexpectedTokenException(makeErrMsg(token));
    }

    repeat = syntaxStackOperation(action, new_state);
      
    analysisInfo +=
      i2string(token -> getInnerLang()) + " " +
      token -> getSourceText() + " action " +
      i2string(action) + " curr state " +
      i2string(this -> syntaxStack.top())
      ;
    
    if (repeat)
      analysisInfo += "\n";

  } while(repeat);

  return analysisInfo;
}

string Analizer::getSemanticOutput() {
  return this -> output.str();
}

bool Analizer::complete() {
  if (this -> gotError)
    return false;

  return (
          this -> syntaxStack.size() == 1 &&
          this -> syntaxStack.top() == INIT_STATE &&
          !this -> gotError
          );
}
/*
 * PRIVATE
 */

/* makes my exceptions look better */
string Analizer::makeErrMsg(Token * token) {
  string errMsg = "";

  errMsg += "syntax error got " + token -> tokenInfo();

  if (this -> lang != NULL) {
    errMsg += " expected ";

    vector<int> expects = this -> syntax -> getTokensWithState(this -> syntaxStack.top());
    for (vector<int>::iterator it = expects.begin(); it != expects.end(); it++)
      errMsg += this -> lang -> getOuterLangValue(*it) + " ";
  }

  return errMsg;
}
