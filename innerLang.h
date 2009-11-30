/* INNERLANG CLASS
 * 
 * Contains inner language.
 *
 * Is able to load inner language values from file.
 *
 * Is able to recognize reserved Lang words .
 * Returns Undefined value if no reserved lang word
 * is found.
 */

#ifndef SMALL_C_LIKE_INNER_LANG
#define SMALL_C_LIKE_INNER_LANG

#include <fstream>
#include <map>

#include "inner_lang_values.h"
#include "textstream.h"

const unsigned int NOT_UNSIGNED_INT = 0;

using namespace std;

typedef map<string, int> innerValueMap;
typedef map<string,int>::iterator innerValueMapInterator;

class InnerLang {
 private:
  ifstream   * file;
  TextStream * stream;
  string       buff;

  innerValueMap LangReservedWords;
  innerValueMapInterator it;

 private:

  /* add to ascii info functionality */
  bool isCharacter(const string *);
  bool isString(const string *);

  /* return innerLangValue */
  int fgetNextInnerValue();

 public:
  InnerLang(string);
  ~InnerLang();

  int getInnerLangValue(string);

};

#endif
