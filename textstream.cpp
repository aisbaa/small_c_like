#include "textstream.h"

using namespace std;

TextStream::TextStream(ifstream * stream) {
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
   * information
   *
   * and 127 officialy is delete
   */
  char currentCharacter = this -> stream -> peek();
  return (
          currentCharacter <= ' ' ||
          currentCharacter >= 127
          );
}

bool TextStream::isDecimalDigit() {
  char currentCharacter = this -> stream -> peek();
  return (currentCharacter >= '0' && currentCharacter <= '9');
}

bool TextStream::isLetter() {
  char currentCharacter = this -> stream -> peek();
  if (currentCharacter >= 'a' && currentCharacter <= 'z') return true;
  if (currentCharacter >= 'A' && currentCharacter <= 'Z') return true;
  return false;
}

bool TextStream::isSpecialCharacter() {
  char currentCharacter = this -> stream -> peek();
  if (currentCharacter >= '!' && currentCharacter <= '/') return true;
  if (currentCharacter >= ':' && currentCharacter <= '@') return true;
  if (currentCharacter >= '[' && currentCharacter <= '`') return true;
  if (currentCharacter >= '{' && currentCharacter <= '~') return true;
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

string TextStream::makeCompareBufferForSkipping(int length) {
  string compareBuffer;
  
  for (int i = 0; i < length; i++)
    if (this -> stream -> good())
      compareBuffer += this -> stream -> get();
    else
      break;

  return compareBuffer;
}

int TextStream::skipToCharacterSequence(const string *pattern) {
  int length = pattern -> length();
  int offset = length;

  string compareBuffer = makeCompareBufferForSkipping(length);

  if (compareBuffer.length() < length)
    return compareBuffer.length();

  /* tries to match the pattern */
  while (
         this -> stream -> good() &&
         &compareBuffer != pattern
         ) {
    compareBuffer += this -> stream -> get();
    compareBuffer.substr(1, length);
    offset++;
  }

  return &compareBuffer == pattern ? 0: offset;
}

/*
 * GETTERS
 */

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

string TextStream::getNextWord() {
  string buffer;

  while (
         this -> stream -> good() &&
         isLetter()
         )
    buffer += this -> stream -> get();

  return buffer;
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
    return "file closed";
    /* I gues it should throw exception */
  }

  if (isDecimalDigit())
    return getNextNumber();

  if (isSpecialCharacter())
    return getNextSpecCharSeq();

  if (isLetter())
    return getNextWord();
}
