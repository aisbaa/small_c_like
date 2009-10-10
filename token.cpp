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

Token::Token(innerValueEntry * value, Position::Position * pos) {
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

/*
 * OPERATORS
 */
/*
string Token::<<opperator () {
  string printThis;

  printThis.append("LangcCode: ");
  printThis.append(itoa(this -> innerLangCode));
  printThis.append(", ");
  printThis.append("SourceText: ");
  printThis.append(this -> sourceText);
  printThis.append(", possitoin to write");

  return printThis;
}
*/
