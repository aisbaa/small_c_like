#ifndef _SMALL_C_LIKE_SEMANTIC_
#define _SMALL_C_LIKE_SEMANTIC_

#include <iostream>
#include <fstream>

#include <vector>
#include <map>

#include "token.h"
#include "textstream.h"

using namespace std;

typedef struct OUTP {
    string * stuff;
    int fromStack; // negative == dont use stack value
    OUTP * next;
} OUTP;

typedef struct SemanticRule {
    unsigned int action;
    unsigned int stackSize;
    int * typeCheckValues; // very c'ish, maybe sould use vector or smth-else
    
    vector<string> outputs;
    //OUTP * output; // here goes outp from file
  /*
    jei tau lengviau su vector - naudok vector vietoj OUTP
    vector<string>
    pagalvojau kad lengvai galiu patikrint ar stringas yra $N formato
   */
    string tokenName;
    
    int innerLangValue;
    int semanticValue;
} SemanticRule;

typedef struct {
    vector<string> firstLine;
    vector<string> secondLine;
    vector<string> thirdLine;
} Block;  

class Semantic {
 private:
  map<int, SemanticRule *> semanticRuleMap;

  TextStream * stream;
  ifstream   * file;

  /*
   * Methods
   */

  void fillMap();

  void parse();
  
  SemanticRule *makeSemanticRule(Block);

  vector<string> getLineColumns();

  Block getBlock();

  int stringToInt(string);
  
 public:
  Semantic(string);

  /* NULL means no semantic rule was found */
  const SemanticRule * getSemanticRule(int);

};

#endif
