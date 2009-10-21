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

#include <string>

using namespace std;

class RulePawn {
 private:
  unsigned int current;

  string rule;
  string buff;

  bool isPassed;

  void checkIfPassed();
  bool isPartOfRule(char);

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
