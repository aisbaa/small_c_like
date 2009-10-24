/* SCANNER CLASS
 * 
 * This class deals with scanning programing
 * language code and creating tokens
 */

#ifndef SMALL_C_LIKE_SCANNER
#define SMALL_C_LIKE_SCANNER

#include <iostream>
#include <fstream>
#include <map>

#include "rulemaster.h"
#include "token.h"

using namespace std;

class Scanner {
 private:
  ifstream   * file;
  RuleMaster * rules;

  bool whiteSpaceSkip;

  /* comment begin => end */
  map<string,string> * comments;

 public:
  /* filename , rules, white space skipping, comment map*/
  Scanner(string, RuleMaster *, bool =true, map<string,string> * =NULL);
  ~Scanner();
  
  /*
   * returns pointer to new Token
   * or NULL if no tokens left
   *
   * maybe should return end of source token
   */
  Token::Token * getNextToken();

 private:
  /*
   * Gets next string based on rules (RuleMaster)
   */
  string getNextLex();

  /*
   * skips white space character until 
   * printable character found
   */
  void skipWhiteSpace();


  /*
   * tell if current lex (from getNextLex)
   * is found in comments map<string,string>
   */
  bool isComment(string);

};

#endif
