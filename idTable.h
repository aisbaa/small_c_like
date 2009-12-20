/**
 * CLASS IdTable
 *
 * 
 */

#ifndef SMALL_C_LIKE_ID_TABLE
#define SMALL_C_LIKE_ID_TABLE

#include <stack>
#include <map>

#include "token.h"

#define SEMA_NONE 0
#define SEMA_VAR  1
#define SEMA_STRC 2
#define SEMA_FNCT 3

using namespace std;

/* contains name and value type that it holds */
typedef map<string, int> Params;

/**
 * sema - semantic value
 * ret  - return value
 * list - list of token that types should be checked
 */
typedef struct {
  int sema, ret;
  Params * list;
} IdTableValue;

typedef struct {
  IdTableValue * checking;
  int step;
} semaCheck;

#define mapPair <string, IdTableValue>
typedef map mapPair IdTableMap;

class IdTable {
 private:
  IdTableMap idTable;

  stack<semaCheck> checkStack;
  stack<int> seqRegStack;
  
 private:
  int getNextFunctParamSemantic();

 public:
  /**
   * Returns true if id has semantic value as passed with int
   */
  bool checkSemanticValue(string, int);

  /**
   * Don't forget to set semantic value to the token befor registrating
   */
  void registrateContinousStart(string name);
  void registrate(string name, int sema, int ret);
  void registrateContinousEnd();
};

#include <stdexcept>

class SemanticError : public logic_error {
public:
   explicit SemanticError(const string err) : logic_error(err) {}
};

#endif
