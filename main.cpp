#include <iostream>
#include <map>

#include "rulepawn.h"
#include "rulemaster.h"
#include "scanner.h"
#include "token.h"

using namespace std;

int main() {
  /*
  RulePawn rule("");
  string str("");

  for (unsigned int i = 0; i < str.length(); i++)
    rule.pass(str[i]);

  cout << (rule.passed() ? "true": "false") << endl;
  */
  /* to show */
  map<string,string> comments;
  comments.insert(pair<string, string>("/*", "*/"));
  comments.insert(pair<string, string>("//", "\n"));

  RuleMaster rules("rules");
  Scanner scanner("testcompiler/example.c", &rules, true);

  Token * token = NULL;
  while (
         (token = scanner.getNextToken())
         != NULL)
    {
      cout << *token << endl;
      delete token;
    }

  return 0;

}
