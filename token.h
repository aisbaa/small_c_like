/**
 * TOKEN CLASS
 *
 * This class contains data for syntax and semantic analizer
 */

#ifndef SMALL_C_LIKE_TOKEN
#define SMALL_C_LIKE_TOKEN

#include <iostream>

#include "position.h"

using namespace std;

class Token {
 private:
  int        innerLangCode;
  int        semanticValue;
  string     sourceText;
  Position * foundIn;

 public:
  Token(int, string, Position *);
  ~Token();

  void setSemanticValue(int value);
  int getSemanticValue();

  int getInnerLang();
  string getSourceText();

  const Position * getPosition();

  friend ostream& operator<<(ostream& tokenInfo, const Token &token);
};

#endif
