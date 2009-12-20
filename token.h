/**
 * TOKEN CLASS
 *
 * This class contains data for syntax and semantic analizer
 */

#ifndef SMALL_C_LIKE_TOKEN
#define SMALL_C_LIKE_TOKEN

#include <iostream>

#include "inner_lang_values.h"
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
  Token(int, int, string);
  ~Token();

  void setSemanticValue(int value);
  int getSemanticValue();

  void setInnerLang(int value);
  int getInnerLang();

  void setSourceText(string text);
  string getSourceText();

  string tokenInfo();

  const Position * getPosition();

  friend ostream& operator<<(ostream& tokenInfo, const Token &token);
};

#endif
