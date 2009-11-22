#include <iostream>
#include <map>

#include "ascii_info.h"

#include "rulemaster.h"
#include "innerLang.h"
#include "scanner.h"
#include "token.h"
#include "matrix.h"
#include "syntax.h"
#include "rewritertool.h"

using namespace std;

int main(int argc, char **argv) {

    RewriterTool tool("test.i");
    InnerLang lang("inner_lang_gen.i");
    Syntax syntax("test.i");

    Matrix matrix(&lang);

/*
  if (argc < 2) {
    cout << "scanner takes one parameter, filename" << endl;
    return 0;
  }

  InnerLang lang("inner_lang_gen.i");

  map<string,string> comments;*/
//comments.insert(pair<string, string>("/*", "*/"));
//comments.insert(pair<string, string>("//", "\n"));
//comments.insert(pair<string, string>("#",  "\n"));
/*
  RuleMaster rules("rules");
  string filename(argv[1]);
  Scanner scanner(&filename, &rules, &lang, &comments,true);

  Token * token = NULL;
  while (
         (token = scanner.getNextToken())
         != NULL)
    {
      cout << *token << endl;
      delete token;
    }
*/
  return 0;

}
