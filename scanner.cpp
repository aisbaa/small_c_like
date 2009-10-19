#include <iostream>
#include <fstream>
#include <istream>
//#include <string>

#include "scanner.h"

using namespace std;

/*
 * INIT && DESTROY
 */

Scanner::Scanner(string fileName, InnerLang * lang, scanerSettings * settings) {
  this -> file = new ifstream(
                              fileName.c_str(),
                              ios_base::in
                              );
  this -> stream = new TextStream((istream *)this -> file);
  this -> lang = lang;

  /* ASSIGN DEFAULTS */
  this -> delimiter = &defaultDelimiter;

  this -> commentOneLineStart   = &defaultCommentOneLineStart;
  this -> commentOneLineEnd     = &defaultCommentOneLineEnd;
  this -> commentMultiLineStart = &defaultCommentMultiLineStart;
  this -> commentMultiLineEnd   = & defaultCommentMultiLineEnd;

  /*
   * gues I should write setting loader
   */
}

Scanner::~Scanner() {
  delete this -> stream;

  if (this -> file -> is_open())
    this -> file -> close();
}

/*
 * COMMENT HANDLING
 */

/* Diagnostic */

bool Scanner::containsOneLineCommentStart() {
  return (this -> buff.find(*this -> commentOneLineStart) != string::npos);
}

bool Scanner::containsMultiLineCommentStart() {
  return (this -> buff.find(*this -> commentMultiLineStart, 0) != string::npos);
}

bool Scanner::containsMultiLineCommentEnd() {
  return (this -> buff.find(*this -> commentMultiLineEnd, 0) != string::npos);
}

/* removing from buff */

void Scanner::removeOneLineComment() {
  this -> buff.erase(this -> buff.find(*this -> commentOneLineStart));
}

void Scanner::removeMultiLineComment() {
  this -> buff.erase(
                     this -> buff.find(*this -> commentMultiLineStart),
                     this -> buff.length()
                     -
                     this -> buff.find(*this -> commentMultiLineEnd)
                     );
}

/* skipping characters in stream */

void Scanner::skipCommentOneLine() {
  string skippedComment = this -> stream -> skipToCharacterSequence(this -> commentOneLineEnd);
}

void Scanner::skipCommentMultiLine() {
  string skippedComment = this -> stream -> skipToCharacterSequence(this -> commentMultiLineEnd);
}


bool Scanner::handlingComments() {
  if (containsOneLineCommentStart()) {

    /* I'm not checking if end of One line comment
     * is in the buffer because it should be new line
     * simbol, and those are skiped by textstream
     */

    removeOneLineComment();
    skipCommentOneLine();

    /* I'll return false here
     * because there shouldn't
     * be any comments left after
     */
    return false;
  }

  if (containsMultiLineCommentStart()) {
    
    /* end of comment is not in the buffer
     * so I skip character in stream to
     * right after comment end
     */
    if (!containsMultiLineCommentEnd())
      skipCommentMultiLine();

    removeMultiLineComment();

    /* I'll return true because
     * it might be atleast one
     * comment left
     *
     * other wise false will be
     * return on next call
     */
    return true;
  }

  return false;
}

/*
 * BUFFER HANDLING
 */

bool Scanner::startsWithStandAloneSimbol(){
  return false;
}

bool Scanner::startsWithStandDoubleSimbol(){
  return false;
}

string Scanner::extractLangEntity() {
  if (startsWithStandDoubleSimbol()) {
    string langEntity = this -> buff.substr(0, 2);
    this -> buff.erase(0, 2);
    return langEntity;
  }

  if (startsWithStandAloneSimbol()) {
    string langEntity = this -> buff.substr(0, 1);
    this -> buff.erase(0, 1);
    return langEntity;
  }

  string langEntity = this -> buff.substr();
  this -> buff.clear();
  return langEntity;
}

/*
 * PUBLIC
 */ 

Token::Token * Scanner::getNextToken() {
  /*
   * 0) padarysiu kad scanneris mokėtų stringus perduot
   */
  if (this -> buff.empty())
    do {
      this -> buff = this -> stream -> getNextEntity();
      while (handlingComments());
    } while (
             this -> buff.empty() &&
             this -> file -> good()
             );

  string singleEntity  = extractLangEntity();

  cout << "single: " << singleEntity << ", buff: " << this -> buff << endl;

  Token::Token * token = new Token(
                                   this -> lang -> getInnerLangValue(singleEntity),
                                   this -> buff,
                                   (Position *)NULL
                                   /* not implemented
                                    * text stream should be
                                    * able to tell this info
                                    */
                                   );

  if (!this -> file -> good())
    return (Token *)NULL;

  return token;

}
