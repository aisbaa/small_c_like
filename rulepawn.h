/* RULEPAWN CLASS
 *
 * this class tells if string matches rule
 *
 * rule supports
 *  "@" - match any letter
 *  "$" - match any number
 *  "*" - match any letter and number
 *  "." - match any ascii character
 *  "\" - escape any character
 */

#ifndef SMALL_C_LIKE_RULEPAWN
#define SMALL_C_LIKE_RULEPAWN

#include <iostream>
#include <queue>
#include <string>

using namespace std;

const string reservedChars  = "@$*.\\";
const string allowPassedIfLastIs = "@$*";

const int noMoreCharacter = -1;

class RulePawn {
 private:
  unsigned int current;

  string rule;

  bool failed;

  /*
   * Case handlers
   */
  bool letterHandler(char, bool =true);
  bool digitHandler(char, bool =true);
  bool letterDigitHandler(char, bool =true);
  bool anyAsciiHandler(char, bool = true);
  bool escapeHandler(char, bool =true);
  bool directMatch(char, bool =true);

  bool nextCharacterMatcher(char);
  bool matchHandler(char, bool =true);

  /* helpers */
  int getNextRuleCharacter();
  bool allowPassedIfLast();

  /* changes rule's state to failed */
  void fail();

 public:
  RulePawn(string);
  ~RulePawn();

  /*tells if rule passed */
  bool passed();

  /* reset all values */
  void reset();

  /* tells if char matches with current char in rule */
  bool pass(char);

  /* this is temp method , will be deleted later */
  string getRule();
};

#endif
