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

/* RULE ONLY
 * every character represents sequence of
 *   letters
 *   digist (decimal)
 *   both letters and digits
 *
 * and the last one represents one escaped simbol
 */

const string reservedChars = "@$*\\";

const int stateChecking = 0;
const int statePassed = 1;
const int stateFailed = 2;

const int checkForDirect = 0;
const int checkForLetter = 1;
const int checkForDigit  = 2;
const int checkForLetterDigit = 3;

class RulePawn {
 private:
  int state;
  int current;

  string rule;

  /* state alters */
  void fail();
  void complete();

  /* handlers */
  bool letterHandler(char);
  bool digitHandler(char);
  bool letterDigitHandler(char);
  bool escapeHandler(char);
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
};

#endif
