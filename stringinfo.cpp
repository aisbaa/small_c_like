#include "stringinfo.h"

/*
 * acourding ascii table, all below 0 (zero, not)
 * originally intended not to represent printable
 * information
 *
 * and 127 officialy is delete
 */
bool isWhiteSpace(char c) {
  return (c <= ' ' || c >= 127);
}

bool isDecimalDigit(char c) {
  return (c >= '0' && c <= '9');
}

bool isLetter(char c) {
  if (c >= 'a' && c <= 'z') return true;
  if (c >= 'A' && c <= 'Z') return true;
  return false;
}

bool isSpecialCharacter(char c) {
  if (c >= '!' && c <= '/') return true;
  if (c >= ':' && c <= '@') return true;
  if (c >= '[' && c <= '`') return true;
  if (c >= '{' && c <= '~') return true;
  return false;
}

/*
 * Now it seems that was designed exponentially XD
 */

/*
 * FOR FUTURE GENERATIONS, PRINTABLE CHARACTERS
 *
 * !"#$%&'()*+,-./0123456789:;<=>?
 * @ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_
 * `abcdefghijklmnopqrstuvwxyz{|}~
 */
