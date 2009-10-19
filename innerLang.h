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
#include <map>

#include "textstream.h"

using namespace std;

const string defaultComment        = "#";
const string defaultCommentLineEnd = "\n";

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

  void getOtherInnerValue(string);

 public:
  InnerLang(string);
  ~InnerLang();

  int getInnerLangValue(string);

};

#endif
