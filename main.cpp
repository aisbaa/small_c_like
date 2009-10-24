#include <iostream>
#include <map>

//#include "rulepawn.h"
#include "rulemaster.h"
#include "scanner.h"
#include "token.h"

using namespace std;

int main() {
  map<string,string> comments;
  comments.insert(pair<string, string>("/*", "*/"));
  comments.insert(pair<string, string>("//", "\n"));
//  comments.insert(pair<string, string>("2", "0"));

  RuleMaster rules("rules");
  Scanner scanner("testcompiler/example.c", &rules, true, &comments);

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
