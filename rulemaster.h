/* RULEMASTER CLASS
 *
 * Handles a bunch of rules
 */

#ifndef SMALL_C_LIKE_RULE_MASTER
#define SMALL_C_LIKE_RULE_MASTER

#include <vector>
#include "rulepawn.h"

using namespace std;

class RuleMaster {
 private:
  vector<RulePawn *> ruleflock;

 public:
  RuleMaster(string);
  ~RuleMaster();

  bool match(char);

  bool haveComplete();

  void reset();
};

#endif
