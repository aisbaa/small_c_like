/**
 * @author: Aistis Jokubauskas
 * @author: Paulius Pilkauskas
 */

#include <iostream>
#include <map>

#include "ascii_info.h"
#include "textstream.h"

#include "innerLang.h"
#include "rulemaster.h"

#include "token.h"

#include "scanner.h"
#include "syntax.h"
#include "semantic.h"
#include "idTable.h"
#include "analizer.h"


using namespace std;

int main(int argc, char **argv) {
   
  if (argc < 2) {
    cout << "scanner takes one parameter, filename" << endl;
    return 0;
  }

  InnerLang lang("inner_lang_gen.i");
  
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
    syntax = new Syntax("inner_augment_grammar_gen.i");
  } catch (InvalidActionInaugmentedGrammar unexp) {
    cerr << "ERROR::Your augmented grammar must be faulty." << endl;
    cerr << "Got " << unexp.what() << endl;
    delete syntax;
    return 1;
  }

  Semantic semantic("inner_semantic_rules.i");
  IdTable idTable;

  Analizer analizer(syntax, &semantic, &idTable, &lang);

  Token * token = NULL;
  while (
         (token = scanner.getNextToken()) != NULL
         )
    try {
      analizer.check(token);
    } catch (UnexpectedTokenException unexp) {
      cerr << unexp.what() << endl;
    } catch (TokenTypeMissMatch miss) {
      cerr << miss.what() << endl;
    }

  delete syntax;

  cout << "---------------------------------" << endl;
  cout << "idTable:"
       << endl
       << idTable;
  cout << "---------------------------------" << endl;
  cout << "program is " << (analizer.complete() ? "correct": "not correct") << endl;
  cout << "semantic output:" << endl
       << analizer.getSemanticOutput();

  return 0;
}
