#include <iostream>
#include <map>

#include "ascii_info.h"
#include "textstream.h"

#include "token.h"

#include "innerLang.h"
#include "rulemaster.h"

#include "scanner.h"
#include "matrix.h"
#include "syntax.h"
#include "analizer.h"

/* make this stand alone */
//#include "rewritertool.h"

using namespace std;

int main(int argc, char **argv) {

  //RewriterTool tool("test.i");
  Syntax * syntax = NULL;
  try {
    syntax = new Syntax("test");
    Matrix matrix(syntax);
  } catch (int) {
    cout << "nothing to read or else" << endl;
  } catch (const char *str) {
    cout << "cought exceptio::" << str << endl;
  } catch (...) {
    cout << "got excpetion" << endl;
  }

  if (argc < 2) {
    cout << "scanner takes one parameter, filename" << endl;
    return 0;
  }

  string filename(argv[1]);

  InnerLang lang("inner_lang_gen.i");
  RuleMaster rules("inner_scanner_scannig_rules");

  map<string,string> comments;
  comments.insert(pair<string, string>("/*", "*/"));
  comments.insert(pair<string, string>("//", "\n"));
  comments.insert(pair<string, string>("#",  "\n"));

  Scanner scanner(&filename, &rules, &lang, &comments,true);
  Analizer analizer(syntax, NULL);

  Token * token = NULL;
  while (
         (token = scanner.getNextToken()) != NULL
         )
    analizer.check(token);

  delete syntax;
  return 0;

}
