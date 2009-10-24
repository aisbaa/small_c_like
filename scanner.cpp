#include <iostream>
#include <fstream>
#include <istream>

#include "ascii_info.h"

#include "rulemaster.h"
#include "rulepawn.h"
#include "scanner.h"
#include "token.h"

using namespace std;

/*
 * PUBLIC
 */

Scanner::Scanner(
                 string fileName,
                 RuleMaster * rules,
                 bool skipWhiteSpace,
                 map<string,string> * comments
                 )
{
  this -> file = new ifstream(
                              fileName.c_str(),
                              ios_base::in
                              );
  this -> rules = rules;

  this -> whiteSpaceSkip = skipWhiteSpace;
  this -> comments = comments;
}

Scanner::~Scanner() {
  if (this -> file -> is_open())
    this -> file -> close();
}

Token::Token * Scanner::getNextToken() {
  string lex;
  do
    lex = getNextLex();
  while (isComment(lex));

  if (lex.length() == 0)
    return NULL;

  return new Token(0, lex, NULL);
}

/*
 * PRIVATE
 */

string Scanner::getNextLex() {
  this -> rules -> reset();

  if (this -> whiteSpaceSkip) skipWhiteSpace();

  bool haveMatched = false;

  string lex;

  while (
         this -> file -> good() &&
         this -> rules -> match((char)this -> file -> peek())
         )
    {
      haveMatched = this -> rules -> haveComplete();
      lex += (char)this -> file -> get();
    }

  if (haveMatched)
    return lex;

  return "";
  /* gues should throw exception */
}

void Scanner::skipWhiteSpace() {
  while (
         this -> file -> good() &&
         isWhiteSpace(this -> file -> peek())
         )
    this -> file -> ignore(1);
}

bool Scanner::isComment(string lex) {
  if (this -> comments == NULL)
    return false;
  
  return false;
  /*
   * map<string,string>::iterator iterator = this -> comments -> find (lex);
   */
}
