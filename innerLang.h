/* INNERLANG CLASS
 * 
 * Contains inner language in dinamic structure.
 *
 * Is able to load inner language values from file
 *
 * Is able to recognize reserved Lang words and
 * return proper value
 */

#ifndef SMALL_C_LIKE_INNER_LANG
#define SMALL_C_LIKE_INNER_LANG

#include <fstream>
#include <queue>

using namespace std;

typedef struct {
  string outervalue;
  int    innervalue;
} innerValue;

class InnerLang {
 private:
  queue<innerValue> LangReservedWords;

 private:
  string fgetNextStringValue();
  int    fgetNextIntValue();

  innerValue fgetNextInnerValue();

 public:
  InnerLang(char*);
  ~InnerLang();

  int getInnerLangValue(string);
};

#endif
