#include <iostream>
#include <queue>
#include <stdlib.h>

#include "ascii_info.h"
#include "rulepawn.h"

using namespace std;

RulePawn::RulePawn(string rule, string additionalLetters) {
  this->rule    = rule;
  this->additionalLetters = additionalLetters;
  reset();
}

RulePawn::~RulePawn() {}

/*
 * PRIVATE HELPERS
 */

int RulePawn::getNextRuleCharacter() {
  if (this->current +1 >= this -> rule.length())
    return noMoreCharacter;

  return this->rule[this->current +1];
}

bool RulePawn::allowPassedIfLast() {
  return (
          allowPassedIfLastIs.find(
                                   this->rule[this->current]
                                   )
          != string::npos
          );
}

bool RulePawn::nextCharacterMatcher(char value) {
  if (getNextRuleCharacter() == noMoreCharacter)
    return false;
  /*
   * so we have next character
   * we need to point to next character in rule
   * and try to match it
   */
  this->current++;

  if (matchHandler(value, false)) // if succeeds with next character
    return true;                  // return true and don't increment this -> current
  // because its already pointing to next rule character
  /*
   * if execution reaches this place
   * this means that test with next
   * character failed
   *
   * so we get back to this charater in rule
   * and this means two steps back, because I
   * forgot why, but it works with two XD
   */
  this->current--;

  return false;
}

/*
 * PRIVATE MATCHERS
 */
bool RulePawn::letterHandler(char value, bool first) {
  if (first)
    if (nextCharacterMatcher(value))
      /* If next character matched */
      return true;

  if (
      !isLetterPlus(value, this -> additionalLetters.c_str())
      )
    {
      if (first) fail();
      return false;
    }

  return true;
}

bool RulePawn::digitHandler(char value, bool first) {
  if (first)
    if (nextCharacterMatcher(value))
      /* If next character matched */
      return true;

  if (!isDecimalDigit(value)) {
    if (first) fail();
    return false;
  }

  return true;
}

bool RulePawn::letterDigitHandler(char value, bool first) {
  if (first)
    if (nextCharacterMatcher(value))
      /* If next character matched */
      return true;

  if (!isDecimalDigit(value) && !isLetterPlus(value, this -> additionalLetters.c_str())) {
    if (first) fail();
    return false;
  } 

  return true;
}

bool RulePawn::anyAsciiHandler(char value, bool first) {
  if (first)
    if (nextCharacterMatcher(value))
      /* If next character matched */
      return true;

  return true;
}

bool RulePawn::endOfLineHandler(char value, bool first) {
  if ('\n' == value) {
    this->current++;
    return true;
  }

  if (first) fail();
  return false;
}

bool RulePawn::escapeHandler(char value, bool first) {
  this -> current++;

  if (!first) {
    /* if im not first */
    if (!directMatch(value, false)) {
      /*
       * I have to take care of this -> current
       * value on fail
       */
      this -> current--;
      return false;
    }
    
    return true;
  }

  return directMatch(value, true);
}

bool RulePawn::directMatch(char value, bool first) {
  if (this->rule[this->current] == value) {
    this->current++;
    return true;
  }

  if (first) fail();
  return false;
}

bool RulePawn::matchHandler(char value, bool first) {
  switch (reservedChars.find(this->rule[this->current])) {
  case 0:
    return letterHandler(value, first);
    break;

  case 1:
    return digitHandler(value, first);
    break;

  case 2:
    return letterDigitHandler(value, first);
    break;

  case 3:
    return anyAsciiHandler(value, first);
    break;

  case 4:
    return endOfLineHandler(value, first);
    break;

  case 5:
    return escapeHandler(value, first);
    break;

  default:
    return directMatch(value, first);
  }

  return false; /* this line must NOT be reached */
}

void RulePawn::fail() {
  this->failed = true;
}

/*
 * Public methods
 */

void RulePawn::reset() {
  this->current = 0;
  this->failed = false;
}

bool RulePawn::passed() {
  if (this->failed)
    return false;

  if (allowPassedIfLast())
    return (
            (this->rule.length() -1)
            == current
            );

  return (this->rule.length() == current);
}

bool RulePawn::pass(char value) {
  if (this->failed)
    return false;

  return matchHandler(value, true);
}

string RulePawn::getRule() {
  return this -> rule;
}
