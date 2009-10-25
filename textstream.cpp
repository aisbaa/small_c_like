#include "textstream.h"

#include <iostream>

using namespace std;

TextStream::TextStream(istream * stream) {
  this -> stream = stream;
}

TextStream::~TextStream() {
  /*
   * user it self must take care of stream closing
   *
   * and at this point there is nothing to be done
   * at destruction
   *
   * or should we close the stream?
   */
}

/*
 * CURRENT CHARACTER METHODS
 */

bool TextStream::isWhiteSpace() {
  /*
   * acourding ascii table, all below space (including)
   * originally intended NOT to represent printable
   * information, so it might not be space, but it should
   * be white
   *
   * and 127 officialy is delete
   */
  char currentCharacter = (char) this -> stream -> peek();
  return (currentCharacter <= ' ' || currentCharacter == (char)127);
}

bool TextStream::isDecimalDigit() {
  char currentCharacter = (char) this -> stream -> peek();
  return (currentCharacter >= '0' && currentCharacter <= '9');
}

bool TextStream::isLetter() {
  char currentCharacter = (char) this -> stream -> peek();
  if ('a' <= currentCharacter && currentCharacter <= 'z') return true;
  if ('A' <= currentCharacter && currentCharacter <= 'Z') return true;
  return false;
}

bool TextStream::isSpecialCharacter() {
  char currentCharacter = (char) this -> stream -> peek();
  if ('!' <= currentCharacter && currentCharacter <= '/') return true;
  if (':' <= currentCharacter && currentCharacter <= '@') return true;
  if ('[' <= currentCharacter && currentCharacter <= '`') return true;
  if ('{' <= currentCharacter && currentCharacter <= '~') return true;
  return false;
} /* Now it seems that ascii designed exponentially XD */

/*
 * SKIPPERS
 */

void TextStream::skipWhiteSpaces() {
  while (
         this -> stream -> good() &&
         isWhiteSpace()
         )
    this -> stream -> ignore(1);
}

string TextStream::getThatMuchCharacters(int length) {
  char * charBuff = new char[length];
  this -> stream -> readsome (charBuff, length);

  string buffer(charBuff, length);
  delete charBuff;
  
  return buffer;
}

string TextStream::skipToCharacterSequence(const string * pattern) {
  int length = pattern -> length();

  string compareBuffer = getThatMuchCharacters(length);
  string returnBuffer   = compareBuffer;

  while (
         this -> stream -> good() &&
         compareBuffer != *pattern
         )
    {
      returnBuffer += this -> stream -> get();
      compareBuffer = returnBuffer.substr(
                                          returnBuffer.length() -length,
                                          length
                                          );
    }

  return returnBuffer;
}

/*
 * GETTERS
 */

string TextStream::getNextWord() {
  string buffer;

  while (
         this -> stream -> good() &&
         isLetter()
         )
    buffer += this -> stream -> get();

  return buffer;
}

string TextStream::getNextNumber() {
  string buffer;

  while (
         this -> stream -> good() &&
         isDecimalDigit()
         )
    buffer += this -> stream -> get();
  
  return buffer;
}


string TextStream::getNextSpecCharSeq() {
  string buffer;
  while (
         this -> stream -> good() &&
         isSpecialCharacter()
         )
    buffer += this -> stream -> get();

  return buffer;
}

string TextStream::getNextSpecialCharacterSequence() {
  return getNextSpecCharSeq();
}

string TextStream::getCharSeqcToPatter(const string * pattern) {
  int length = pattern -> length();

  string compareBuffer = getThatMuchCharacters(length);
  string returnBuffer  = compareBuffer;

  while (
         this -> stream -> good() &&
         compareBuffer != *pattern
         )
    {
      returnBuffer += this -> stream -> get();
      compareBuffer = returnBuffer.substr(
                                          returnBuffer.length() -length,
                                          length
                                          );
    }

  return returnBuffer;
}

/*
 * Three above a bit repetative
 */

/*
 * USER STUFF
 */

string TextStream::getNextEntity() {
  skipWhiteSpaces();
  
  if (!this -> stream -> good()) {
    return "bad stream";
    /* I gues it should throw exception */
  }

  if (TextStream::isDecimalDigit())
    return getNextNumber();

  if (TextStream::isSpecialCharacter())
    return getNextSpecCharSeq();

  if (TextStream::isLetter())
    return getNextWord();

  return "";
}
