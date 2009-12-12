#ifndef _SMALL_C_LIKE_SEMANTIC_
#define _SMALL_C_LIKE_SEMANTIC_

#include <iostream>
#include <fstream>
#include <vector>

#include "token.h"
#include "textstream.h"

using namespace std;

typedef struct OUTP {
    string * stuff;
    int fromStack; // negative == dont use stack value
    OUTP * next;
} OUTP;

typedef struct SemanticRule {
    unsigned int stackSize;
    int * typeCheckValues; // very c'ish, maybe sould use vector or smth-else
    
    OUTP * output; // here goes outp from file
    
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

  string makeValue();

  SemanticRule *makeSemanticRule(Block);

  vector<string> getLineColumns(int);

  vector<OUTP> makeOutp(vector<string>);

  Block getBlock();

  int stringToInt(string);

 public:
  Semantic(string);

  void printBlock(Block);
  void printSemanticRule(SemanticRule *);

  /* NULL means no semantic rule was found */
  SemanticRule * getSemanticRule(int);

};

#endif
