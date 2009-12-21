/**
 * CLASS Analizer
 *
 * This class controls syntax and semantic analisys.
 * Has stack with innerLang values for syntax purpose
 * Has stack with tokens for semantic purpose 
 */

#ifndef SMALL_C_LIKE_ANALIZER
#define SMALL_C_LIKE_ANALIZER

#include <iostream>
#include <sstream>

#include <stack>

#include "innerLang.h"
#include "syntax.h"
#include "semantic.h"
#include "idTable.h"
#include "token.h"

using namespace std;

typedef vector<Token *> TokensInUse;
class Analizer {
 private:
  InnerLang * lang;
  Syntax    * syntax;
  Semantic  * semantic;

  IdTable * idTable;

  ostringstream output;

  bool gotErrorSyntax;
  bool gotErrorSemantic;

  stack<int> syntaxStack;
  stack<Token *> semanticStack;
  stack<Token *> tokenDump;

  int currRegType;
  unsigned int tmpVarCnt;

 public:
  Analizer(Syntax *, Semantic * =NULL, IdTable * = NULL, InnerLang * =NULL);
  ~Analizer();

  /**
   * Returns syntactic reduction done on one token
   */
  string check(Token *);

  string getSemanticOutput();

  bool complete();

 private:

  /*
   * SYNTAX
   */
  /**
   * returns true if you should call syntaxStackOperation method with the same token
   * returns false if no additional call is needed.
   */
  bool syntaxStackOperation(int, int);

  /**
   * Makes my exception mesages look better
   */
  string makeErrMsg(Token *);

  /*
   * SEMANTIC
   */
  /**
   * checks semantic stuff and generetes pseudo code
   */
  void semanticStackOperation(int);

  /**
   * Logical parts of semanticStackOperation method
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
   * puts stuff to semanticStack accourding to the rule
   */
  void semanticPutStuffToStack(const SemanticRule *, TokensInUse *);

  /**
   * Returns pionter to string that should be output.
   */
  const string semanticSelectOutputStr(const string * tokenName, TokensInUse * tokens);

  /**
   * Utils
   */

  /**
   * puts tokens to tokenDump stack
   */
  void clienTokens(TokensInUse *);

};

#include <stdexcept>

class TokenTypeMissMatch : public logic_error {
public:
   explicit TokenTypeMissMatch(const string err) : logic_error(err) {}
};


#endif
