#include <iostream>
#include <sstream>

#include "../textstream.h"
#include "textstream_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION (testTextStream);

void testTextStream::setUp (void) {
  digitStream = new stringstream(digits, ios_base::in);

  CPPUNIT_ASSERT(digitStream -> str() == digits);
  digitTextStream = new TextStream(digitStream);

  letterStream = new stringstream(letters, ios_base::out);
  letterTextStream = new TextStream(letterStream);
  CPPUNIT_ASSERT(letterStream -> str() == letters);

  specCharsStream = new stringstream(specChars, ios_base::out);
  specCharsTextStream = new TextStream(specCharsStream);
  CPPUNIT_ASSERT(specCharsStream -> str() == specChars);

  whiteSpacesStream = new stringstream(whiteSpace, ios_base::out);
  whiteSpacesTextStream = new TextStream(whiteSpacesStream);
  CPPUNIT_ASSERT(whiteSpacesStream -> str() ==  whiteSpace);

  commentStream = new stringstream(comment, ios_base::out);
  commentTextStream = new TextStream(commentStream);
  CPPUNIT_ASSERT(commentStream -> str() ==  comment);

}

void testTextStream::tearDown (void) {
  delete digitStream;
  delete digitTextStream;

  delete letterStream;
  delete letterTextStream;

  delete specCharsStream;
  delete specCharsTextStream;

  delete whiteSpacesStream;
  delete whiteSpacesTextStream;

  delete commentStream;
  delete commentTextStream;
}

/*
 * isTests
 */

void testTextStream::test_isDecimalDigit(void) {
  CPPUNIT_ASSERT(digitTextStream -> isDecimalDigit());
  CPPUNIT_ASSERT(!letterTextStream -> isDecimalDigit());
  CPPUNIT_ASSERT(!specCharsTextStream -> isDecimalDigit());
  CPPUNIT_ASSERT(!whiteSpacesTextStream -> isDecimalDigit());
  CPPUNIT_ASSERT(!commentTextStream -> isDecimalDigit());
}

void testTextStream::test_isLetter(void) {
  CPPUNIT_ASSERT(!digitTextStream -> isLetter());
  CPPUNIT_ASSERT(letterTextStream -> isLetter());
  CPPUNIT_ASSERT(!specCharsTextStream -> isLetter());
  CPPUNIT_ASSERT(!whiteSpacesTextStream -> isLetter());
  CPPUNIT_ASSERT(!commentTextStream -> isLetter());
}

void testTextStream::test_isSpecialCharacter(void) {
  CPPUNIT_ASSERT(!digitTextStream -> isSpecialCharacter());
  CPPUNIT_ASSERT(!letterTextStream -> isSpecialCharacter());
  CPPUNIT_ASSERT(specCharsTextStream -> isSpecialCharacter());
  CPPUNIT_ASSERT(!whiteSpacesTextStream -> isSpecialCharacter());
  CPPUNIT_ASSERT(commentTextStream -> isSpecialCharacter());
}

void testTextStream::test_isWhiteSpace(void) {
  CPPUNIT_ASSERT(!digitTextStream -> isWhiteSpace());
  CPPUNIT_ASSERT(!letterTextStream -> isWhiteSpace());
  CPPUNIT_ASSERT(!specCharsTextStream -> isWhiteSpace());
  CPPUNIT_ASSERT(whiteSpacesTextStream -> isWhiteSpace());
  CPPUNIT_ASSERT(!commentTextStream -> isWhiteSpace());
}
