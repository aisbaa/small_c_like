#include <iostream>

#include "rulemaster.h"
#include "rulepawn.h"
#include "scanner.h"
#include "token.h"

using namespace std;

int main() {
  /* test rulepawn */
  /*
  string str = "x,";
  RulePawn rule("@");
  for (unsigned int i = 0; i < str.length(); i++) {
    rule.pass(str[i]);
  }
  cout << "rule  " << (rule.passed() ? "passed": "didn't") << endl;

  RuleMaster testRules("rules2");
  for (unsigned int i = 0; i < str.length(); i++) {
    testRules.match(str[i]);
  }

  cout << "rules " <<(testRules.haveComplete() ? "passed": "didn't") << endl;
  */
  RuleMaster rules("rules");
  Scanner scanner("testcompiler/example.c", &rules);

  while (scanner.getNextToken() != NULL);

  return 0;

}
