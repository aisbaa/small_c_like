#include "token.h"
#include "position.h"

#include "textstream.h"

using namespace std;

/*
 * INIT && DESTROY
 */

Token::Token(int innerLangCode, string sourceText, Position::Position * foundIn) {
  this -> innerLangCode = innerLangCode;
  this -> semanticValue = UNDEFINED;
  this -> sourceText = sourceText;
  this -> foundIn = foundIn;
}

Token::Token(int innerLangCode, int semanticValue, string sourceText) {
  this -> innerLangCode = innerLangCode;
  this -> semanticValue = semanticValue;
  this -> sourceText = sourceText;
  this -> foundIn = NULL;
}

Token::~Token() {
  if (this -> foundIn != NULL)
    delete this -> foundIn;
}

/*
 * GETTERS && SETTERS
 */

void Token::setSemanticValue(int value) {
  this -> semanticValue = value;
}

int Token::getSemanticValue() {
  return this -> semanticValue;
}

/*-*/
void Token::setInnerLang(int value) {
  this -> innerLangCode = value;
}

int Token::getInnerLang() {
  return this -> innerLangCode;
}
/*-*/
void Token::setSourceText(string text) {
  this -> sourceText = text;
}

string Token::getSourceText() {
  return this -> sourceText;
}

const Position::Position * Token::getPosition() {
  return this -> foundIn;
}

string Token::tokenInfo() {
  string info = this -> sourceText;
  if (this -> foundIn != NULL) {
    info += " ";
    info += i2string(this -> foundIn -> getLine());
    info += ":";
    info += i2string(this -> foundIn -> getCol());
  }
  return info;
}

ostream& operator<<(ostream& tokenInfo, const Token &token) {
  tokenInfo.width(4);

  tokenInfo << token.innerLangCode
            << " "
            << token.semanticValue;

  tokenInfo.width(8);
  tokenInfo << token.sourceText;

  if (token.foundIn != (Position *)NULL)
    tokenInfo << " "
              << *(token.foundIn);

  return tokenInfo;
}
