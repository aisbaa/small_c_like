/**
 * CLASS ANALIZER
 *
 * This class controls syntax and semantic analisys.
 * Has stack with syntax only information
 */

#ifndef ANALIZER
#define ANALIZER

#include <stack>

#include "innerLang.h"
#include "syntax.h"
#include "token.h"

using namespace std;

class Analizer {
 private:
  InnerLang * lang;
  Syntax * syntax;
  void * semantic;

  bool gotError;

  stack<int> stateStack;

 public:
  Analizer(Syntax *, void * =NULL, InnerLang * =NULL);

  void check(Token *);

  bool complete();
};

#endif
