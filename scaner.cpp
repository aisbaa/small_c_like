#include <fstream>
#include "scaner.h"

using namespace std;

Scaner::Scaner(char *fileName, InnerLang* lang) {
  this -> file.open(fileName, ifstream::in);
}

Scaner::~Scaner() {
  if (this -> file.is_open())
    this -> file.close();
}

Token::Token * get_tocken() {
  Token *token = NULL;
  return token;
}
