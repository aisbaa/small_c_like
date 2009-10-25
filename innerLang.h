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

#include "textstream.h"

using namespace std;

const string defaultComment        = "#";
const string defaultCommentLineEnd = "\n";
const int    defaultUndefinedValue = 99;

typedef map<string, int> innerValueMap;

class InnerLang {

  ifstream   * file;
  TextStream * stream;
  string       buff;

 private:
  innerValueMap LangReservedWords;
  map<string,int>::iterator it;

  int otherInnerValue;

  const string * comment;
  const string * commentLineEnd;

 private:
  bool   containsAtBegining(const string *, const string *);
  bool   isCommentOneLine();
  bool   isComment();
  void   skipComment();

  bool   isDigit();

  void fgetNextInnerValue();

 public:
  InnerLang(string);
  ~InnerLang();

  int getInnerLangValue(string);

};

#endif
