/* SCANNER CLASS
 * 
 * This class deals with scanning programing language code
 * and creating tokens
 */

#ifndef SMALL_C_LIKE_SCANNER
#define SMALL_C_LIKE_SCANNER

#include <iostream>
#include <fstream>

#include "rulemaster.h"
#include "rulepawn.h"
#include "token.h"

using namespace std;

class Scanner {
 private:
  ifstream   * file;
  RuleMaster * rules;

  bool whiteSpaceSkip;
  bool commentSkip;

 public:
  Scanner(string, RuleMaster *, bool =true, bool =false);
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
