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
#include <map>

#include "token.h"
#include "innerLang.h"
#include "textstream.h"

using namespace std;

const string defaultDelimiter = " ";

const string defaultCharacterThatCanApearInSigles  = "( ) { } [ ] + - * / = ;";
const string defaultCharacterThatCanApearInDoubles = "() {} [] ++ -- += -= *= /= ==";

const string defaultCommentOneLineStart = "//";
const string defaultCommentOneLineEnd   = "\n";

const string defaultCommentMultiLineStart = "/*";
const string defaultCommentMultiLineEnd   = "*/";

typedef struct {
  string * characterThatCanApearInSigles;
  string * characterThatCanApearInDoubles;

  string * commentOneLine;
  string * commentMultiLine;

} scanerSettings;

class Scanner {
 private:
  string       buff;   // contains value got from stream -> getNextEntity()
  InnerLang  * lang;   // pointer to inner language object

  ifstream   * file;   // source file
  TextStream * stream; // object for text stream functionality


  const string * delimiter;

  queue<string>       characterThatCanApearInSigles;
  map<string, string> characterThatCanApearInDoubles;

  const string * commentOneLineStart;
  const string * commentOneLineEnd;

  const string * commentMultiLineStart;
  const string * commentMultiLineEnd;

 public:
  /* if file fails to opens - throws exemption (not implemented) */
  Scanner(string, InnerLang *, scanerSettings * =NULL);
  ~Scanner();
  
  /*
   * returns pointer to new Token
   * or NULL if no tokens left
   *
   * maybe should return end of source token
   */
  Token::Token * getNextToken();

 private:
  /* big helpers */
  string extractLangEntity();
  bool handlingComments();

  /* diagnostic */
  bool containsOneLineCommentStart();
  bool containsMultiLineCommentStart();
  bool containsMultiLineCommentEnd();

  bool startsWithStandAloneSimbol();
  bool startsWithStandDoubleSimbol();

  /* small helpers */
  void removeOneLineComment();
  void removeMultiLineComment();

  void skipCommentOneLine();
  void skipCommentMultiLine();

};

#endif
