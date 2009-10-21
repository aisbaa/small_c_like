#include <stdbool.h>
#include "ascii_info.h"

bool isWhiteSpace(char character) {
  /*
   * acourding ascii table, all below space (including)
   * originally intended NOT to represent printable
   * information, so it might not be space, but it should
   * be white
   *
   * and 127 officialy is delete
   */
  return (character <= ' ' || character == (char)127);
}


bool isDecimalDigit(char character) {
  return (character >= '0' && character <= '9');
}

bool isLetter(char character) {
  if ('a' <= character && character <= 'z') return true;
  if ('A' <= character && character <= 'Z') return true;
  return false;
}

bool isSpecialCharacter(char character) {
  if ('!' <= character && character <= '/') return true;
  if (':' <= character && character <= '@') return true;
  if ('[' <= character && character <= '`') return true;
  if ('{' <= character && character <= '~') return true;
  return false;
} /* Now it seems that ascii designed exponentially XD */
