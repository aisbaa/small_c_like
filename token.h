/* TOKEN CLASS
 *
 * This class contains data for syntax analizer
 */

#ifndef SMALL_C_LIKE_TOKEN
#define SMALL_C_LIKE_TOKEN

#include <iostream>
//#include <string>

#include "position.h"
#include "innerLang.h"

using namespace std;

class Token {
 private:
  int        innerLangCode;
  string     sourceText;
  Position * foundIn;

 public:
  Token(int, string, Position *);
  ~Token();

  int getInnerLang();
  string getSourceText();

  const Position * getPosition();
  /*
   * sould have operator << for cout
   */
};

#endif
