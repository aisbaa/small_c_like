/* INNERLANG CLASS
 * 
 * Contains inner language in dinamic structure.
 *
 * Is able to load inner language values from file
 *
 * Is able to recognize reserved Lang words and
 * return proper value
 *
 * Is able to return correct innerLangValue
 */

#ifndef SMALL_C_LIKE_INNER_LANG
#define SMALL_C_LIKE_INNER_LANG

#include <fstream>
#include <queue>

using namespace std;

typedef struct {
  string outervalue;
  int    innervalue;
} innerValueEntry;

class InnerLang {
 private:
  queue<innerValueEntry *> LangReservedWords;

 private:
  /* for loading LangReservedWords */
  string fgetNextStringValue();
  int    fgetNextIntValue();

  innerValueEntry * fgetNextInnerValue();

 public:
  InnerLang(string);
  ~InnerLang();

  int getInnerLangValue(string *);
};

#endif
