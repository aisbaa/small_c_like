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

using namespace std;

const char   defaultDelimiter = ' ';

const string defaultCharacterThatCanApearInSigles  = "( ) { } [ ] + - * / = ;";
const string defaultCharacterThatCanApearInDoubles = "() {} [] ++ -- += -= *= /= ==";

const string defaultComment0 = "// \n";
const string defaultComment1 = "/* */";

typedef struct {
  string * characterThatCanApearInSigles;
  string * characterThatCanApearInDoubles;

  string * commentOneLine;
  string * commentMultyLine;

} scanerSettings;

class Scanner {
  ifstream   * file;
  TextStream * stream;
  InnerLang  * lang;

  const char     defaultDelimiter;

  const string * characterThatCanApearInSigles;
  const string * characterThatCanApearInDoubles;

  const string * commentOneLine;
  const string * commentMultyLine;

 private:


  /* tells if given string is start of comment (witch is second string) */
  bool isStartOfCommrnt(const string *, const string *);

  /*
   * skips comments,
   * file pointer must point to first character of comment
   * otherwise lots of text will be lost
   */
  void skipComments(string, string);

 public:
  /* if file fails to opens - throws exemption (not implemented) */
  Scanner(string, InnerLang *, scanerSettings * = NULL);
  ~Scanner();
  
  Token::Token * getNextToken();
};

#endif
