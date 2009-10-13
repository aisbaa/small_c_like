#include <iostream>
#include <fstream>
#include <istream>
//#include <string>

#include "scanner.h"

using namespace std;

/*
 * INIT && DESTROY
 */

Scanner::Scanner(string fileName, InnerLang * lang) {
  this -> file = new ifstream(
                              fileName.c_str(),
                              ios_base::in
                              );
  this -> stream = new TextStream((istream *)this -> file);
  this -> lang = lang;

  /* ASSIGN DEFAULTS */
  this -> commentOneLineStart   = &defaultCommentOneLineStart;
  this -> commentOneLineEnd     = &defaultCommentOneLineEnd;
  this -> commentMultyLineStart = &defaultCommentMultyLineStart;
  this -> commentMultyLineEnd   = & defaultCommentMultyLineEnd;
}

Scanner::~Scanner() {
  delete this -> stream;

  if (this -> file -> is_open())
    this -> file -> close();
}

/*
 * PRIVATE UTILS
 */

bool Scanner::containsAtBegining(const string * base, const string * needle) {
  string compare =  base -> substr(0, needle -> length());
  return (compare == *needle);  
}

bool Scanner::isCommentOneLine() {
  return containsAtBegining(
                            &(this -> buff),
                            this -> commentOneLineStart
                            );
}

bool Scanner::isCommentMultyLine() {
  return containsAtBegining(
                            &(this -> buff),
                            this -> commentMultyLineStart
                            );
}

bool Scanner::isComment() {
  return (
          isCommentOneLine() ||
          isCommentMultyLine()
          );
}

void Scanner::skipComment() {
  string skippedComment;

  if (isCommentOneLine())
    skippedComment = this -> stream -> skipToCharacterSequence(this -> commentOneLineEnd);

  if (isCommentMultyLine())
    skippedComment = this -> stream -> skipToCharacterSequence(this -> commentMultyLineEnd);

  /*
   * should I check if skippedComment contains end of comment
   * if end of comment isn't present - what when?
   */
}

/*
 * USER METHODS
 */

Token::Token * Scanner::getNextToken() {
  do {
    this -> buff = this -> stream -> getNextEntity();
    if (isComment()) skipComment();
  } while (isComment());

  cout.width(15);
  cout << this -> buff << endl;

  return (this -> file -> good() ?
          (Token::Token *)!NULL:
          (Token::Token *)NULL
          );

}
