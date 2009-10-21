#include <iostream>
#include <fstream>
#include <istream>


#include "scanner.h"

using namespace std;

/*
 * INIT && DESTROY
 */

Scanner::Scanner(string fileName, RuleMaster * rules, bool skipWhiteSpace, bool skipComments) {
  this -> file = new ifstream(
                              fileName.c_str(),
                              ios_base::in
                              );
  this -> rules = rules;

  this -> skipWhiteSpace = skipWhiteSpace;
  this -> skipComments   = skipComments;
}

Scanner::~Scanner() {
  /*
   * Should I take care of king ?
   */
  if (this -> file -> is_open())
    this -> file -> close();
}

string Scanner::getNextLex() {
  this -> rules -> reset();

  if (this -> skipWhiteSpace) skipWhiteSpace();

  bool stillHave = false;
  bool haveMatched = false;

  string lex;

  while (
         this -> file -> good() &&
         bool pass = rules.match(this -> file -> peek()) 
         )
    {
      /* these has one step back info */
      stillHave   = pass;
      haveMatched = rules.haveComplete();

      lex += (char)this -> file -> get();
    }

  if (haveMatched && stillHave)
    return lex;

  return "";
  /* gues should throw exception */
}

void Scanner::skipWhiteSpace() {
  while (
         this -> file -> good() &&
         isWhiteSpace(this -> file -> peek())
         )
    this -> file -> ignore(1)
}
