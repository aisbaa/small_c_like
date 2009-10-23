#include <iostream>
#include <queue>
#include <stdlib.h>

#include "ascii_info.h"
#include "rulepawn.h"

using namespace std;

RulePawn::RulePawn(string rule) {
  this->rule    = rule;
  reset();
}

RulePawn::~RulePawn() {}

/*
 * Private methods
 */

/*
 * HELPERS
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
  if (getNextRuleCharacter() != noMoreCharacter) {
    /*
     * has next character
     * so we point to next character in rule
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
    this->current -= 2;
  }

  return false;
}

/*
 * MATCHERS
 */
bool RulePawn::letterHandler(char value, bool first) {
  if (first)
    if (nextCharacterMatcher(value))
      /* If next character matched */
      return true;

  if (!isLetter(value)) {
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

  if (!isDecimalDigit(value) && !isLetter(value)) {
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

bool RulePawn::escapeHandler(char value, bool first) {
  this -> current++; // hope over escape character
  return directMatch(value);
}

bool RulePawn::directMatch(char value, bool first) {
  if (this->rule[this->current++] == value)
    return true;

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
