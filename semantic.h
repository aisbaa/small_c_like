#ifndef _SMALL_C_LIKE_SEMANTIC_
#define _SMALL_C_LIKE_SEMANTIC_

#include "token.h"

typedef OUTP {
  string * stuff;
  int fromStack; // negative == dont use stack value
  OUTP * next;
}

typedef semanticRule {
  unsigned int stackSize;
  int * typeCheckValues; // very c'ish, maybe sould use vector or smth-else

  OUTP * output; // here goes outp from file

  string tokenName;

  int innerLangValue;
  int semanticValue;
} semanticRule;

clas Semantic {
 private:
  map<int, semanticRule *> semanticRuleMap;

 public:
  Semantic(string);

  /* NULL means no semantic rule was found */
  const semanticRule * getSemanticRule(int);
};

#endif
