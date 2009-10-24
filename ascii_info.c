#include <stdbool.h>
#include <string.h>
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


bool isAtBeginnig(const char * str1, const char *str2) {
  unsigned int one = 0, two = 0;

  while (str1[one] != '\0' && str2[two] != '\0')
    if (str1[one] != str2[two]) return false;

  return true;
}

bool isAtEnd(const char * str1, const char * str2) {
  unsigned int one = strlen(str1) -1;
  unsigned int two = strlen(str2) -1;

  for (
       unsigned int index = (one > two ? one : two);
       index >= 0;
       index--
       )
    if (str1[one -index] != str1[two -index])
      return false;

  return false;
}
