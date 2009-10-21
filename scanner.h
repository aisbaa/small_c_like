/* SCANNER CLASS
 * 
 * This class deals with scanning programing language code
 * and creating tokens
 */

#ifndef SMALL_C_LIKE_SCANNER
#define SMALL_C_LIKE_SCANNER

#include <iostream>
#include <fstream>

#include "token.h"

using namespace std;

class Scanner {
 private:
  ifstream   * file;
  RuleMaster * rules;

  bool skipWhiteSpace = true;
  bool skipComments   = false;

 public:
  Scanner(string, RuleMaster *, bool, bool);
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
   * Gets next string based on king (RuleMaster)
   * rule set
   */
  string getNextLex();

  /*
   * skips white space character until 
   * printable character found
   */
  void skipWhiteSpace();

};

#endif
