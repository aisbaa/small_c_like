#include <iostream>

#include "stringinfo.h"
#include "innerLang.h"
#include "scaner.h"

using namespace std;

int main() {
  InnerLang lang("grammar.i");
  Scaner scaner("testcompiler/simple.c", &lang);
  while (scaner.getNextToken() != NULL);
}
