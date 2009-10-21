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

const string defaultAnyAlnum  = "*";
const string defaultAnyAlpha  = "@";
const string defaultAnyNumber = "$";

class RulePawn {
 private:
  int current;

  string rule;
  string buff;

  bool isPassed;
  bool hasAny;
  bool hasAnyAlnum;
  bool hasAnyAlpha;
  bool hasAnyNumber;

  string anyAlnum;
  string anyAlpha;
  string anyNumber;

  queue<int> anyAlnumPositions;
  queue<int> anyAlphaPositions;
  queue<int> anyNumberPositions;

  int currentAnyAlnumPosition;
  int currentAnyAlphaPosition;
  int currentAnyNumberPosition;

  int anyCharacterPosition;

  void getNextAlnumPosition();
  void getNextAlphaPosition();
  void getNextNumberPosition();

  void checkIfPassed();

  bool isLetter(char);
  bool isNumber(char);

  bool skipAnyAlnum(char);
  bool skipAnyAlpha(char);
  bool skipAnyNumber(char);

  bool isPartOfRule(char);
  bool isPartOfRuleWithSpec(char);
  bool isPartOfRuleWithoutSpec(char);

  void hasRuleAnyCharacter();

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
