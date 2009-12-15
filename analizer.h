/**
 * CLASS ANALIZER
 *
 * This class controls syntax and semantic analisys.
 * Has stack with innerLang values for syntax purpose
 * Has stack with tokens for semantic purpose 
 */

#ifndef ANALIZER
#define ANALIZER

#include <iostream>
#include <sstream>

#include <stack>

#include "innerLang.h"
#include "syntax.h"
#include "semantic.h"
#include "token.h"

using namespace std;

/* name and semantic value */
typedef struct {
  int semanticValue;
  int semanticClass;
} IdTableValue;

typedef vector<Token *> TokensInUse;
typedef map<string, IdTableValue> IdTable;
class Analizer {
 private:
  InnerLang * lang;
  Syntax    * syntax;
  Semantic  * semantic;

  IdTable idTable; // table for variables, function names, struct names, new types

  ostringstream output;

  bool gotErrorSyntax;
  bool gotErrorSemantic;

  stack<int> syntaxStack;
  stack<Token *> semanticStack;
  stack<Token *> tokenDump;

 private:
  string makeErrMsg(Token *);

  /**
   * returns true if you should call syntaxStackOperation method with the same token
   * returns false if no additional call is needed.
   */
  bool syntaxStackOperation(int, int);


  /**
   * checks semantic stuff and generetes pseudo code
   */
  void semanticStackOperation(int);

  /**
   * logical parts of semanticStackOperation method
   */

  /**
   * preformes deep check on token
   */
  bool deepTypeCheck(int , Token *);

  /**
   * pops tokens of semanticStack to the vector
   */
  TokensInUse * getSemanticTokens(const unsigned int, vector<int> types);

  /**
   * prints pseudo code to output atribute
   */
  void semanticPrintStuff(vector<string>, TokensInUse *);

  /**
   * Utils
   */

  /**
   * puts tokens to tokenDump stack
   */
  void clienTokens(TokensInUse *);

 public:
  Analizer(Syntax *, Semantic * =NULL, InnerLang * =NULL);
  ~Analizer();

  /* returns analysis information */
  string check(Token *);
  string getSemanticOutput();

  bool complete();
};

#include <stdexcept>

class TokenTypeMissMatch : public logic_error {
public:
   explicit TokenTypeMissMatch(const string err) : logic_error(err) {}
};


#endif
