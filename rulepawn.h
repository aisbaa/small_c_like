/* RULEPAWN CLASS
 *
 * this class tells if string matches rule
 *
 * string fed by single character
 *
 * rule should support as single statment
 *   any ascii char
 *   white space character (tab, newline, maybe other)
 *   digit
 *   alphabetic
 *   special char
 *
 * "@" - match any letter
 * "$" - match any number
 * "*" - match any letter and number
 */

#ifndef SMALL_C_LIKE_RULEPAWN
#define SMALL_C_LIKE_RULEPAWN

#include <iostream>
#include <queue>
#include <string>

using namespace std;

const string reservedChars  = "@$*\\";

const string anyLetterDigit = "*";
const string anyLetter      = "@";
const string anyDigit       = "$";

class RulePawn {
 private:
  int current;

  string rule;
  string buff;

  int handlerCounter;

  bool isLetter(char);
  bool isDigit(char);

  bool letterHandler(char);
  bool digitHandler(char);
  bool letterDigitHandler(char);
  bool direcMatch(char);

 public:
  RulePawn(string);
  ~RulePawn();

  /*tells if rule passed */
  bool passed();

  /* reset all values */
  void reset();

  /* tells if char matches with current char in rule */
  bool pass(char);

  string getRule();
};

#endif
