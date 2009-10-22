#include <iostream>
#include <queue>
#include <stdlib.h>

#include "ascii_info.h"
#include "rulepawn.h"

using namespace std;

RulePawn::RulePawn(string rule) {
  this->rule    = rule;
  this->current = 0;

  this->handlerCounter = 0;
}

RulePawn::~RulePawn() {}

/*
 * Private methods
 */

bool RulePawn::letterHandler(char value) {
  if (!this->buff[this->current]) this->buff += anyLetter;
  if (this->rule[this->current+1] == value && this->handlerCounter > 0) {
    this->handlerCounter = 0;
	this->buff += value;
	this->current += 2;
    return true;
  }
  if (isLetter(value)) {
    this->handlerCounter++;
    return true;
  }
  if (isDecimalDigit(value)) {
    this->handlerCounter = 0;
    this->current++;
    return pass(value);
  }
  this->buff += value;
  return false;
}

bool RulePawn::digitHandler(char value) {
  if (!this->buff[this->current]) this->buff += anyDigit;
  if (this->rule[this->current+1] == value && this->handlerCounter > 0) {
    this->handlerCounter = 0;
	this->buff += value;
	this->current += 2;
    return true;
  }
  if (isDecimalDigit(value)) {
    this->handlerCounter++;
    return true;
  }
  if (isLetter(value)) {
    this->handlerCounter = 0;
    this->current++;
    return pass(value);
  }
  this->buff += value;
  return false;
}

bool RulePawn::letterDigitHandler(char value) {
  if (!this->buff[this->current]) this->buff += anyLetterDigit;
  if (this->rule[this->current+1] == value && this->handlerCounter > 0) {
    this->handlerCounter = 0;
	this->buff += value;
	this->current += 2;
    return true;
  }
  this->handlerCounter++;
  if (isDecimalDigit(value) || isLetter(value)) return true;
  this->buff += value;
  return false;
}

bool RulePawn::escapeHandler(char value) {
  this -> current++; // hope over escape
  if (this -> rule[this -> current++] == value)
    return true;

  return false;
}

bool RulePawn::directMatch(char value) {
  this->buff += value;
  if (this->rule[this->current++] == value)
    return true;

  return false;
}

/*
 * Public methods
 */

void RulePawn::reset() {
  this->current = 0;
  this->buff    = "";

  this->handlerCounter = 0;
}

bool RulePawn::passed() {
  if (this->buff == this->rule) return true;
  return false;
}

bool RulePawn::pass(char value) {
  switch (reservedChars.find(this->rule[this->current])) {
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
      return directMatch(value);
    }

  return false; /* this line must NOT be reached */
}

string RulePawn::getRule() {
  return this -> rule;
}
