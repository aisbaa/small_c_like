#include <iostream>
#include <fstream>
#include <string>

#include "stringinfo.h"
#include "scanner.h"

using namespace std;

/*
 * INIT && DESTROY
 */

Scanner::Scanner(string fileName, InnerLang * lang, scanerSettings * settings ) {
  this -> file = new ifstream(
                              fileName.c_str(),
                              ios_base::in
                              );
  this -> lang = lang;

  if (settings != NULL) {
    this -> characterThatCanApearInSigles  = settings -> characterThatCanApearInSigles;
    this -> characterThatCanApearInDoubles = settings -> characterThatCanApearInDoubles;
  } else {
    this -> characterThatCanApearInSigles  = &defaultCharacterThatCanApearInSigles;
    this -> characterThatCanApearInDoubles = &defaultCharacterThatCanApearInDoubles;
  }
}

Scanner::~Scanner() {
  if (this -> file -> is_open())
    this -> file -> close();
}

/*
 * PRIVATE UTILS
 */


/*
 * USER METHODS
 */

Token::Token * Scanner::getNextToken() {
  string sourceString = Scanner::getNextEntity();
  cout << sourceString << endl;
  return ( this -> file -> is_open() ?
           (Token::Token *)!NULL:
           (Token::Token *)NULL
           );
}
