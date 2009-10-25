#include <stdbool.h>

#ifndef AISBAA_ASCII_INFO
#define AISBAA_ASCII_INFO

bool isWhiteSpace(char);

bool isDecimalDigit(char);

bool isLetter(char);

bool isLetterPlus(char, const char *);

bool isSpecialCharacter(char);

bool containsCharacter(const char *, char);

#endif
