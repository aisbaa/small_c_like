#include <iostream>

#include "rulemaster.h"
#include "rulepawn.h"
#include "token.h"

using namespace std;

int main() {
  /* test rulepawn */
  string str = "3rAAgfgBB33737CC3h3hAAyryBB3737CC";
  RulePawn rule("*AA@BB$CC*AA@BB$CC");

  int loop = str.length();
  for (int i = 0; i < loop; i++) {
    rule.pass(str[i]);
  }

  if (rule.passed())
    cout << "Priklauso" << endl;
  else
    cout << "Nepriklauso" << endl;

  /* test rulemaster */
  RuleMaster rules("rules");
  string testLex = "ford";

  for (unsigned int index = 0; index < testLex.length(); index++) {
    cout << (rules.match(testLex[index]) ? "yey": "boo") << " ";
    cout << rules.haveComplete() << endl;
  }

  return 0;

}
