/* SCANNER CLASS
 * 
 * This class deals with scanning programing language code
 * and creating tokens
 */

#ifndef SMALL_C_LIKE_SCANNER
#define SMALL_C_LIKE_SCANNER
#include <iostream>
#include <fstream>
#include <string>

#include "token.h"
#include "innerLang.h"
#include "textstream.h"

using namespace std;

const char   defaultDelimiter = ' ';

const string defaultCharacterThatCanApearInSigles  = "( ) { } [ ] + - * / = ;";
const string defaultCharacterThatCanApearInDoubles = "() {} [] ++ -- += -= *= /= ==";

const string defaultCommentOneLineStart = "//";
const string defaultCommentOneLineEnd   = "\n";

const string defaultCommentMultyLineStart = "/*";
const string defaultCommentMultyLineEnd   = "*/";

typedef struct {
  string * characterThatCanApearInSigles;
  string * characterThatCanApearInDoubles;

  string * commentOneLine;
  string * commentMultyLine;

} scanerSettings;

class Scanner {
  string       buff;
  InnerLang  * lang;

  ifstream   * file;
  TextStream * stream;

  /*
  //const char     delimiter;

  const string * characterThatCanApearInSigles;
  const string * characterThatCanApearInDoubles;
  */

  const string * commentOneLineStart;
  const string * commentOneLineEnd;

  const string * commentMultyLineStart;
  const string * commentMultyLineEnd;

 private:
  /* tells if first string contains second string at its begening */
  bool containsAtBegining(const string *, const string *);
  /* tells if content in buff is single line comment start */
  bool isCommentOneLine();

  /* tells if content in buff is multy line comment start */
  bool isCommentMultyLine();

  /* checks if content in buff is comment */
  bool isComment();

  /* skips comment */
  void skipComment();

 public:
  /* if file fails to opens - throws exemption (not implemented) */
  Scanner(string, InnerLang *);
  ~Scanner();
  
  Token::Token * getNextToken();
};

#endif
