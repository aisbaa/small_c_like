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
#include "textstream.h"

using namespace std;

const string defaultComment        = "#";
const string defaultCommentLineEnd = "\n";

typedef struct {
  string outervalue;
  int    innervalue;
} innerValueEntry;

class InnerLang {

  ifstream   * file;
  TextStream * stream;
  string       buff;

 private:
  queue<innerValueEntry *> LangReservedWords;

  const string * comment;
  const string * commentLineEnd;

 private:
  /* for loading LangReservedWords */
  //string fgetNextStringValue();
  //int    fgetNextIntValue();
  int    searchInnerLangValue(string);

  bool   containsAtBegining(const string *, const string *);
  bool   isCommentOneLine();
  bool   isComment();
  void   skipComment();

  bool   isDigit();

  innerValueEntry * fgetNextInnerValue();

 public:
  InnerLang(string);
  ~InnerLang();

  int getInnerLangValue(string);

};

#endif
