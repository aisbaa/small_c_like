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
 * for example a@b should match
 * ab, abb, acb, aaab, asdfghjklb...
 */

#ifndef SMALL_C_LIKE_RULEPAWN
#define SMALL_C_LIKE_RULEPAWN

#include <iostream>
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

  int anyAlnumPosition;
  int anyAlphaPosition;
  int anyNumberPosition;

  int anyCharacterPosition;

  void checkIfPassed();

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
