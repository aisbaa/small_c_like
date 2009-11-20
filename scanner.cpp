#include <iostream>
#include <fstream>
#include <istream>

#include "ascii_info.h"

#include "rulemaster.h"
#include "rulepawn.h"
#include "scanner.h"
#include "position.h"
#include "token.h"

using namespace std;

/*
 * PUBLIC
 */

Scanner::Scanner(
                 string * filename,
                 RuleMaster * rules,
                 InnerLang * lang,
                 map<string,string> * comments,
                 bool skipWhiteSpace
                 )
{
  this -> file = new ifstream(
                              filename -> c_str(),
                              ios_base::in
                              );
  this -> rules = rules;
  this -> lang  = lang;

  this -> comments = comments;
  this -> whiteSpaceSkip = skipWhiteSpace;

  this -> filename = filename;
  this -> line = 1;
  this -> col  = 1;
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

  return new Token(
                   this -> lang -> getInnerLangValue(lex),
                   lex,
                   new Position(this -> filename, this -> line, this -> col - lex.length())
                   );
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
      char curr = (char)this -> file -> get();
      haveMatched = this -> rules -> haveComplete();
      lex += curr;

      if (curr == '\n') {
        this -> line++;
        this -> col = 0;
      }
      
      this -> col++;
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
    {
      char curr = (char)this -> file -> get(); 

      if (curr == '\n') {
        this -> line++;
        this -> col = 0;
      }
      
      this -> col++;
    }
}

bool Scanner::strContains(string contains, string needle, bool front) {
  if (contains.length() < needle.length())
    return false;

  string extract;

  if (front)
    extract = contains.substr(0, needle.length());
  else
    extract = contains.substr(contains.length() -needle.length());

  return (extract == needle);
}

bool Scanner::isComment(string lex) {
  const bool front = true;
  const bool tail = false;

  if (this -> comments == NULL)
    return false;

  for (
       map<string,string>::iterator commentIterator = this -> comments -> begin();
       commentIterator != this -> comments -> end();
       commentIterator++
       )
    if (
        strContains(lex, commentIterator -> first, front) &&
        strContains(lex, commentIterator -> second, tail)
        )
      return true;
  
  return false;
}
