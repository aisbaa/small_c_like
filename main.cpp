#include <iostream>

#include "innerLang.h"
#include "scanner.h"

using namespace std;

int main() {
  InnerLang lang("grammar.i");
  Scanner scanner("testcompiler/stress.c", &lang);
  while (scanner.getNextToken() != NULL);
}
