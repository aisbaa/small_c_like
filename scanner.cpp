#include <iostream>
#include <fstream>
#include <string>

#include "stringinfo.h"
#include "scaner.h"

using namespace std;

/*
 * INIT && DESTROY
 */

Scaner::Scaner(string fileName, InnerLang* lang) {
  this -> file = new ifstream(
			     fileName.c_str(),
			     ios_base::in
			     );
  this -> lang = lang;
}

Scaner::~Scaner() {
  if (this -> file -> is_open())
    this -> file -> close();
}

/*
 * PRIVATE UTILS
 */

void Scaner::skipWhiteSpaces() {
  while (
         this -> file -> good()
         && isWhiteSpace(
                         this -> file -> peek()
                         )
         )
    this -> file -> ignore(1);
}

/* - */
void Scaner::skipComments(string start, string end) {
  for (int startAnalizerIndex = 0; startAnalizerIndex < start.lenght(); startAnalizerIndex++)
    if (start[startAnalizerIndex] != this -> file -> peek()) {
      this -> file -> unread(startAnalizerIndex);
      break;
    } else {
      this -> file -> ignore(1);
    }

  while ()
}

/* - */
string Scaner::getNextNumber() {
  string buffer;

  while (
         this -> file -> good()
         && isDecimalDigit(
                               this -> file -> peek()
                               )
         )
      buffer += this -> file -> get();

  return buffer;
}

/* - */
string Scaner::getNextStatement() {
  string buffer;

  while (
         this -> file -> good()
         && isSpecialCharacter(
                               this -> file -> peek()
                               )
         )
      buffer += this -> file -> get();

  return buffer;
}

/* - */
string Scaner::getNextWord() {
  string buffer;

  while (
         this -> file -> good()
         && isLetter(
                     this -> file -> peek()
                     )
         )
      buffer += this -> file -> get();

  return buffer;
}

/*
 * RPIVATE BASE - Switch like method
 */

string Scaner::getNextEntity() {
  Scaner::skipWhiteSpaces();
  
  if (!this -> file -> good()) {
    if (this -> file -> is_open()) this -> file -> close();
    return "file closed";
  }
  
  char fristchar = this -> file -> peek();

  if (isDecimalDigit(fristchar))
    return Scaner::getNextNumber();

  if (isSpecialCharacter(fristchar))
    return Scaner::getNextStatement();

  if (isLetter(fristchar))
    return Scaner::getNextWord();
}

/*
 * USER METHODS
 */

Token::Token * Scaner::getNextToken() {
  string sourceString = Scaner::getNextEntity();
  cout << sourceString << endl;
  return ( this -> file -> is_open() ?
           (Token::Token *)!NULL:
           (Token::Token *)NULL
          );
}
