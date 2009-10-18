#include "token.h"
#include "innerLang.h"
#include "position.h"

/*
 * better to use internal values or call getters to get those ?
 */

using namespace std;

/*
 * INIT && DESTROY
 */

Token::Token(int innerLangCode, string sourceText, Position::Position * foundIn) {
  this -> innerLangCode = innerLangCode;
  this -> sourceText = sourceText;
  this -> foundIn = foundIn;
}

Token::~Token() {
  if (this -> foundIn != NULL)
    delete this -> foundIn;
}

/*
 * GETTERS
 */

int Token::getInnerLang() {
  return this -> innerLangCode;
}

string Token::getSourceText() {
  return this -> sourceText;
}


const Position::Position * Token::getPosition() {
  return this -> foundIn;
}
