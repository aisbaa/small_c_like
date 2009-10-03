/* SCANER CLASS
 * 
 * This class deals with scaning programing language code
 * and creating tokens
 */

#ifndef SMALL_C_LIKE_SCANER
#define SMALL_C_LIKE_SCANER

#include <fstream>
#include "token.h"
#include "innerLang.h"

using namespace std;

class Scaner {
  ifstream   file;
  InnerLang* lang;

 private:
  string getWord();

 public:
  /* if no file opens trows exeption */
  Scaner(char*, InnerLang*);
  ~Scaner();
  
  Token::Token * get_tocken();
};

#endif
