#include "rulepawn.h"

using namespace std;

RulePawn::RulePawn(string rule) {
  this->rule     = rule;
  this->current  = -1;
  this->isPassed = false;
}

RulePawn::~RulePawn() {}

/*
 * Private methods
 */

void RulePawn::checkIfPassed() {
  if (this->buff == this->rule)
    this->isPassed = true;
  else
    this->isPassed = false;
}

bool RulePawn::isPartOfRule(char value) {
  checkIfPassed();
  if (this->rule[this->current] == value) return true;
  return false;
}

/*
 * Public methods
 */

void RulePawn::reset() {
  this->buff     = "";
  this->current  = -1;
  this->isPassed = false;
}

bool RulePawn::passed() {
  return this->isPassed;
}

bool RulePawn::pass(char value) {
  this->buff += value;
  this->current += 1;
  return isPartOfRule(value);
}
