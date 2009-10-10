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

class Scanner {
  ifstream  *file;
  InnerLang *lang;

 private:
  /* skips space character until finds non space */
  void skipWhiteSpaces();

  /*
   * skips comments,
   * file pointer must point to first character of comment
   * otherwise lots of text will be lost
   */
  void skipComments(string, string);

  /* gets next word, file pointer must point to first letter */
  string getNextWord();

  /* gets next natural number, file pointer must point to first digit */
  string getNextNumber();

  /* gets next statement (+ - * / ... ), file pointer must point to first ...? */
  string getNextStatement();

  /*
   * gets next entity, which could be any of
   *   getNextWord
   *   getNextNumber
   *   getNextStatement
   *
   * automatically skips white spaces and comments
   */
  string getNextEntity();

 public:
  /* if file fails to opens - throws exemption (not implemented) */
  Scanner(string, InnerLang*);
  ~Scaner();
  
  Token::Token * getNextToken();
};

#endif
