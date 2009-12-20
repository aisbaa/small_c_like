#include <stdlib.h>

#include <stack>
#include <vector>

#include "semantic.h"
#include "syntax.h"
#include "token.h"

#include "inner_lang_values.h" // action, type checking values
#include "analizer.h"

Analizer::Analizer(Syntax * syntax, Semantic * semantic, IdTable * idTable, InnerLang * lang) {
  if (syntax == NULL) throw "Analizer can't check without Syntax object.";
  this -> syntax = syntax;

  this -> semantic = semantic;
  this -> idTable = idTable;
  this -> lang = lang;

  this -> gotErrorSyntax = false;
  this -> gotErrorSemantic = false;

  this -> syntaxStack.push(INIT_STATE);
}

Analizer::~Analizer() {
  while (!this -> semanticStack.empty()) {
    delete this -> semanticStack.top();
    this -> semanticStack.pop();
  }

  while (!this -> tokenDump.empty()) {
    delete this -> tokenDump.top();
    this -> tokenDump.pop();
  }
}

/*
 * Small public utils
 */

string Analizer::getSemanticOutput() {
  return this -> output.str();
}

bool Analizer::complete() {
  if (this -> gotErrorSyntax || this -> gotErrorSemantic)
    return false;

  return (
          this -> syntaxStack.size() == 1 &&
          this -> syntaxStack.top() == INIT_STATE
          );
}

/*
 * PUBLIC || SHOULD SAY BASE METHOD
 */

string Analizer::check(Token * token) {
  this -> semanticStack.push(token);

  bool repeat;
  string analysisInfo;

  do {
    int action = -1;
    int new_state;

    try { /* Syntax */
      action = this -> syntax -> getNextState(this -> syntaxStack.top(), token -> getInnerLang(), &new_state);
      repeat = syntaxStackOperation(action, new_state);
    } catch (UnexpectedTokenException unexp) {
      this -> gotErrorSyntax = true;
      throw UnexpectedTokenException(makeErrMsg(token));
    }

    try { /* Semantic */
      if (!this -> gotErrorSemantic && this -> semantic != NULL)
        semanticStackOperation(new_state);
    } catch(TokenTypeMissMatch) {
      this -> gotErrorSemantic = true;
      throw;
    }

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

/*
 * Syntax Methods
 */

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

/* makes my exceptions look better */
string Analizer::makeErrMsg(Token * token) {
  string errMsg = "";

  errMsg += "syntax error got ";
  errMsg += token -> getSourceText();

  if (this -> lang != NULL) {
    errMsg += " expected ";

    vector<int> expects = this -> syntax -> getTokensWithState(this -> syntaxStack.top());
    for (vector<int>::iterator it = expects.begin(); it != expects.end(); it++)
      errMsg += this -> lang -> getOuterLangValue(*it) + " ";
  }

  return errMsg;
}

/*
 * Semantic
 */

void Analizer::semanticStackOperation(int state) {
  const SemanticRule * rule = this -> semantic -> getSemanticRule(state);
  if (rule == NULL) return;

  TokensInUse * tokensInUse = getSemanticTokens(rule -> stackSize, rule -> typeCheckValues);  
 
  semanticPrintStuff(rule -> outputs, tokensInUse);
  semanticPutStuffToStack(rule, tokensInUse);
  
  clienTokens(tokensInUse);
}

/*
 * Gets that many tokens as howMuch tells and checks their types
 */

TokensInUse * Analizer::getSemanticTokens(const unsigned int howMuch, vector<int>  types) {
  string failMsg;
  TokensInUse * workWith = new TokensInUse;

  for (unsigned int pops = 0; pops < howMuch; pops++) {
    workWith -> push_back(this -> semanticStack.top());

    if (types[pops] != DONT_CHECK)
      if (!deepTypeCheck(types[pops], this -> semanticStack.top()))
        failMsg = "type miss matched with " + this -> semanticStack.top() -> tokenInfo();

    this -> semanticStack.pop();
  }

  if (failMsg.size() > 0) {
    clienTokens(workWith);
    throw TokenTypeMissMatch(failMsg);
  }

  return workWith;
}

/*
 * deep type checking preformed
 * checks id table
 */
bool Analizer::deepTypeCheck(int mustBe, Token * token) {
  if (token -> getInnerLang() == mustBe) return true;
  // todo
  return false;
}

/*
 * prints pseudo code
 */
void Analizer::semanticPrintStuff(vector<string> stuff, TokensInUse * tokens) {
  if (stuff.at(0) == DONT_OUTPUT_SC) return;

  for (unsigned int i = 0; i < stuff.size(); i++) {
    if (stuff.at(i).at(0) == '$')
      this -> output << tokens -> at(atoi(stuff.at(i).substr(1).c_str())) -> getSourceText();
    else
      this -> output << stuff.at(i);

    this -> output << " ";
  }

  this -> output << endl;
}

/*
 *
 */
void Analizer::semanticPutStuffToStack(const SemanticRule *rule, TokensInUse * tokens) {
  if (rule -> innerLangValue == DONT_PUSH) return;

  Token * token = new Token(
                            rule -> innerLangValue,
                            rule -> semanticValue,
                            semanticSelectOutputStr(&(rule -> tokenName), tokens)
                            );
  this -> semanticStack.push(token);
}

/*
 * private utils
 */
const string Analizer::semanticSelectOutputStr(const string * tokenName, TokensInUse * tokens) {
  if (tokenName -> at(0) != '$')
    return string(*tokenName) ;

  Token * token  = tokens -> at(atoi(tokenName -> substr(1).c_str()));
  return token -> getSourceText();
}

void Analizer::clienTokens(TokensInUse * tokens) {
  for (unsigned int i = tokens -> size(); i > 0; i--) {
    this -> tokenDump.push(tokens -> back());
    tokens -> pop_back();
  }
  delete tokens;
}

