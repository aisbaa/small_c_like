#include <iostream>

#include "innerLang.h"
#include "scanner.h"
#include "token.h"

using namespace std;

int main() {
  InnerLang lang("grammar.i");
  Scanner scanner("testcompiler/simple.c", &lang);

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
    }
}
