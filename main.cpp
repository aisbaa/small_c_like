#include <iostream>

#include "rulemaster.h"
//#include "scanner.h"
#include "token.h"

using namespace std;

int main() {
  RuleMaster rules("rules");
  string testLex = "ford";

  for (unsigned int index = 0; index < testLex.length(); index++) {
    cout << (rules.match(testLex[index]) ? "yey": "boo") << " ";
    cout << rules.haveComplete() << endl;
  }

  return 0;
}
