/* SCANNER CLASS
 * 
 * This class deals with scanning programing
 * language code and creating tokens
 */

#ifndef SMALL_C_LIKE_SCANNER
#define SMALL_C_LIKE_SCANNER

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "rulemaster.h"
#include "innerLang.h"
#include "position.h"
#include "token.h"

using namespace std;

class Scanner {
 private:
  ifstream   * file;
  RuleMaster * rules;
  InnerLang  * lang;

  string * filename;
  int line, col;

  /* comment begin => end */
  map<string,string> * comments;

  bool whiteSpaceSkip;

 public:
  /* filename , rules, white space skipping, comment map*/
  Scanner(
          string *,
          RuleMaster *,
          InnerLang *,
          map<string,string> *,
          bool
          );
  ~Scanner();
  
  /**
   * returns pointer to new Token
   * or NULL if no tokens left
   *
   * maybe should return end of source token
   */
  Token::Token * getNextToken();

 private:
  /**
   * Gets next string based on rules (RuleMaster)
   */
  string getNextLex();

  /**
   * skips white space character until 
   * printable character found
   */
  void skipWhiteSpace();

  /**
   * tell if current lex (from getNextLex)
   * is found in comments map<string,string>
   */
  bool isComment(string lex);

  /**
   * checks if needle is at front or back
   *
   * needle should be smaller then contains
   * if not so - false will be returned
   *
   * does not check if NULL is passed
   */
  bool strContains(string, string, bool = true);

};

#endif
