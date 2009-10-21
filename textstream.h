/*
 * UNIT TESTING TELLS THAT methods 
 *   isLetter
 *   isWhiteSpace
 *   isSpecialCharacter
 * does NOT work!!!
 * but maybe it's because of me low knolage on unit testing XD
 */

/* TEXTSTREAM CLASS
 *
 * This class wraps around istream
 * and adds some functionality
 */

#ifndef AISBAA_TEXT_STREAM
#define AISBAA_TEXT_STREAM

using namespace std;

//#include <iostream>
#include <istream>

class TextStream {
 private:
  istream * stream;

 public:
  TextStream(istream *);
  ~TextStream();

  /*
   * CHARACTER METHODS
   */

  /* tells if current character (pointed by filepointer) is decimal digit */
  bool isDecimalDigit();

  /* tells if current character (pointed by filepointer) is letter */
  bool isLetter();

  /*
   * tells if current character (pointed by filepointer) is special character.
   * and these are
   *   non decimal
   *   non letter
   *   non white space
   */
  bool isSpecialCharacter();

  /* tells if current character (pointed by filepointer) is non pritable character */
  bool isWhiteSpace();

  /*
   * SKIPPING CHARACTER SEQUENCES
   */

  /* skips whote space characters until finds non white space */
  void skipWhiteSpaces();

  /* extracts that much characters from stream */
  string getThatMuchCharacters(int);

  /*
   * skips any number of character until finds given pattern
   */
  string skipToCharacterSequence(const string *);

  /*
   * GETTERS
   */

  /* gets next word, file pointer must point to first letter */
  string getNextWord();

  /* gets next natural number, file pointer must point to first digit */
  string getNextNumber();

  /* gets next statement (+ - * / ... ), file pointer must point to first ...? */
  string getNextSpecialCharacterSequence();
  string getNextSpecCharSeq();
  
  string getCharSeqcToPatter(const string *);
  string getCharSeqcToPatter(const string);

  /*
   * SUMMARY
   */

  /*
   * gets string, which could be any of
   *   getNextWord
   *   getNextNumber
   *   getNextStatement
   *
   * automatically skips white spaces and comments
   */
  string getNextEntity();

};

#endif
