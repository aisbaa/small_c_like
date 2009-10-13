#ifndef TEST_AISBAA_TEXT_STREAM
#define TEST_AISBAA_TEXT_STREAM

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <sstream>
#include "../textstream.h"

using namespace std;

const string digits = "0123456789";
const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string specChars = "!\"#$%&\'()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
const string whiteSpace = " \t\n";
const string comment = "/* skip this */ hello";

class testTextStream : public CPPUNIT_NS :: TestFixture {

  CPPUNIT_TEST_SUITE (testTextStream);
  CPPUNIT_TEST (test_isDecimalDigit);
  CPPUNIT_TEST (test_isLetter);
  CPPUNIT_TEST (test_isSpecialCharacter);
  CPPUNIT_TEST (test_isWhiteSpace);
  CPPUNIT_TEST_SUITE_END ();

 public:
  void setUp (void);
  void tearDown (void);

 protected:
  void test_isDecimalDigit(void);
  void test_isLetter(void);
  void test_isSpecialCharacter(void);
  void test_isWhiteSpace(void);

 private:
  stringstream
    * digitStream,
    * letterStream,
    * specCharsStream,
    * whiteSpacesStream,
    * commentStream
    ;

  TextStream
    * digitTextStream,
    * letterTextStream,
    * specCharsTextStream,
    * whiteSpacesTextStream,
    * commentTextStream
    ;
};

#endif
