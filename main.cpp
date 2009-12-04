#include <iostream>
#include <map>

#include "ascii_info.h"
#include "textstream.h"

#include "innerLang.h"
#include "rulemaster.h"

#include "token.h"

#include "scanner.h"
#include "syntax.h"
#include "analizer.h"

using namespace std;

int main(int argc, char **argv) {
   
  if (argc < 2) {
    cout << "scanner takes one parameter, filename" << endl;
    return 0;
  }

  InnerLang lang("inner_lang_gen.i");
  
  cout << "test: ',' is " << lang.getInnerLangValue(",") << endl;
  
  RuleMaster rules("inner_scanner_scannig_rules");

  map<string,string> comments;
  comments.insert(pair<string, string>("/*", "*/"));
  comments.insert(pair<string, string>("//", "\n"));
  comments.insert(pair<string, string>("#",  "\n"));

  bool skipWhiteSpaces = true;
  string filename(argv[1]);
  Scanner scanner(&filename, &rules, &lang, &comments, skipWhiteSpaces);

  Syntax * syntax = NULL;
  try {
    syntax = new Syntax("inner_augment_grammar_human.i");
  } catch (InvalidActionInaugmentedGrammar unexp) {
    cerr << "ERROR::Your augmented grammar must be faulty." << endl;
    cerr << unexp.what() << endl;
    delete syntax;
    return 1;
  }

  Analizer analizer(syntax, NULL);

  Token * token = NULL;
  while (
         (token = scanner.getNextToken()) != NULL
         )
    analizer.check(token);

  delete syntax;
  cout << "program is " << (analizer.complete() ? "correct": "not correct") << endl;

  return 0;

}
