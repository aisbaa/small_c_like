#include <iostream>
#include <map>

#include "ascii_info.h"

#include "rulemaster.h"
#include "innerLang.h"
#include "scanner.h"
#include "token.h"

using namespace std;

int main() {
  InnerLang lang("inner_lang_gen.i");

  map<string,string> comments;
  comments.insert(pair<string, string>("/*", "*/"));
  comments.insert(pair<string, string>("//", "\n"));
  comments.insert(pair<string, string>("#",  "\n"));

  RuleMaster rules("rules");
  Scanner scanner("testcompiler/stress.c", &rules, &lang, &comments,true);

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
