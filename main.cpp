#include <iostream>

#include "innerLang.h"
#include "scanner.h"
#include "token.h"
#include "rulepawn.h"

using namespace std;

int main() {
  string str = "3rAAgfgBB33737CC3h3hAAyryBB3737CC";

  RulePawn rule("*AA@BB$CC*AA@BB$CC");

  int loop = str.length();
  for (int i = 0; i < loop; i++) {
    rule.pass(str[i]);
  }
  if (rule.passed()) cout << "Priklauso" << endl;
  else cout << "Nepriklauso" << endl;

/*  InnerLang lang("grammar.i");
  Scanner scanner("testcompiler/example.c", &lang);

  Token::Token * token = NULL;
  while (
         (token = scanner.getNextToken()) != NULL
         )
    {
      cout << token -> getSourceText()
           << " "
           << token -> getInnerLang()
           << endl;

      delete token;
    }*/
}
