/**
 * CLASS ANALIZER
 *
 * This class controls syntax and semantic analisys.
 * Has stack with innerLang values for syntax purpose
 * Has stack with tokens for semantic purpose 
 */

#ifndef ANALIZER
#define ANALIZER

#include <iostream>
#include <sstream>

#include <stack>

#include "innerLang.h"
#include "syntax.h"
#include "semantic.h"
#include "token.h"

using namespace std;

class Analizer {
 private:
  InnerLang * lang;
  Syntax    * syntax;
  Semantic  * semantic;

  ostringstream output;

  bool gotError;

  stack<int> syntaxStack;
  stack<Token *> semanticStack;

 private:
  string makeErrMsg(Token *);

  bool syntaxStackOperation(int, int);
  void semanticStackOperation(int);

 public:
  Analizer(Syntax *, Semantic * =NULL, InnerLang * =NULL);
  ~Analizer();

  /* returns analysis information */
  string check(Token *);
  string getSemanticOutput();

  bool complete();
};

#endif
