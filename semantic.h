#ifndef _SMALL_C_LIKE_SEMANTIC_
#define _SMALL_C_LIKE_SEMANTIC_

#include <iostream>
#include <fstream>

#include <vector>
#include <map>

#include "token.h"
#include "textstream.h"

using namespace std;

typedef struct SemanticRule {
    unsigned int action;
    unsigned int stackSize;
    vector<int> typeCheckValues;
    
    vector<string> outputs;

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
  vector<int> makeTypeCheckValues(vector<string>);

  Block getBlock();

  int stringToInt(string);
  
 public:
  Semantic(string);

  /* NULL means no semantic rule was found */
  const SemanticRule * getSemanticRule(int);

};

#endif
