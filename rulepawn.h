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

 public:
  /* rule must be pased */
  RulePawn(string);

  /*tells if rule passed */
  bool pass();

  /* tells if char matches with current char in rule */
  bool pass(char);
};

#endif
