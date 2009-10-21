#include <iostream>
#include <string>

#include "rulepawn2.h"

using namespace std;

RulePawn::RulePawn(string rule) {
  this -> rule    = rule;
  reset();
}

RulePawn::~RulePawn() {
}

/*
 * PRIVATE
 */

bool RulePawn::ruleSpecialCase() {
  return reservedChars.find(this -> rule[current]) != string::npos;
}

bool RulePawn::letterHandler(char value) {
}

bool RulePawn::digitHandler(char value) {
}

bool RulePawn::letterDigitHandler(char value) {
}

bool RulePawn::escapeHandler(char value) {
}

bool RulePawn::direcMatch(char value) {
  if (this -> rule[this -> current++] == value) {
    complete();
    return true;
  }

  fail();
  return false;
}

/* STATE ALTERS */
void RulePawn::fail() {
  this -> state = stateFailed;
}

void RulePawn::complete() {
  /*
   * if passed beyoned last rule char
   * this means that rule is complete
   */
  return this -> rule.length() == this -> current;
}

/*
 * PUBLIC
 */

void RulePawn::reset() {
  this -> current = 0;
}

bool RulePawn::passed() {
  return state == statePassed;
}

bool RulePawn::pass(char value) {
  if (failed())
    return false;

  /* if rule was complete on last call
   * this means that it must fail now
   * 
   * P.S. theres no such this as more complete
   */
  if (complete()) {
    fail();
    return false;
  }

  /*
   * case values check reservedChars const
   * character place represents case value
   */
  switch (
          reservedChars.find(this -> rule[this -> current])
          )
    {
    case 0:
      return letterHandler(value);
      break;
    
    case 1:
      return digitHandler(value);
      break;

    case 2:
      return letterDigitHandler(value);
      break;

    case 3:
      return escapeHandler(value);
      break;

    default:
      return direcMatch(value);
    }
  
  return false; /* this line must NOT be reached */
}
