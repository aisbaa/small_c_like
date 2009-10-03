/* TOKEN CLASS
 *
 * This class contains data for syntax analizer
 */

#ifndef SMALL_C_LIKE_TOKEN
#define SMALL_C_LIKE_TOKEN

#include <string>

#include "position.h"
#include "innerLang.h"

using namespace std;

class Token {
 private:
  int       innerLang;
  string    sourceText;
  Position* foundIn;

 public:
  Token(innerValue*, Position*);
  ~Token(){};

  int getInnerLang();

  string getSourceText();
  const Position * getPosition();

};

#endif
