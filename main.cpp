#include <iostream>

#include "rulemaster.h"
#include "rulepawn.h"
#include "scanner.h"
#include "token.h"

using namespace std;

int main() {
  /* test rulepawn */

  string str = "cordinates { }";
  RulePawn rule("@");

  int loop = str.length();
  for (int i = 0; i < loop; i++) {
    rule.pass(str[i]);
  }

  if (rule.passed())
    cout << "Priklauso" << endl;
  else
    cout << "Nepriklauso" << endl;


  RuleMaster rules("rules");
  Scanner scanner("testcompiler/example.c", &rules);

  while (scanner.getNextToken() != NULL);

  return 0;

}
