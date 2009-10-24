#include <stdbool.h>

#ifndef AISBAA_ASCII_INFO
#define AISBAA_ASCII_INFO

bool isWhiteSpace(char);

bool isDecimalDigit(char);

bool isLetter(char);

bool isSpecialCharacter(char);

/* returns last char index */

bool isAtBeginnig(const char *, const char *);

bool isAtEnd(const char *, const char *);

#endif
