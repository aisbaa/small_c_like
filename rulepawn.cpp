#include "rulepawn.h"

using namespace std;

RulePawn::RulePawn(string rule) {
  this->rule       = rule;
  this->whiteSpace = &defaultWhiteSpace;
  this->current    = -1;
  this->isPassed   = false;
  this->notStarted = true;
}

RulePawn::~RulePawn() {}

/*
 * Private methods
 */

bool RulePawn::isPartOfRule(char value) {
  if (this->rule[this->current] == value) return true;
  return false;
}

/*
 * Public methods
 */

void RulePawn::reset() {
  this->current    = -1;
  this->buff       = "";
  this->isPassed   = false;
  this->notStarted = true;
}

bool RulePawn::passed() {
  return this->isPassed;
}

bool RulePawn::pass(char value) {
  if (!passed()) {
    if (value == this->whiteSpace[0]) {
      this->current += 1;
      this->buff += value;
      return isPartOfRule(value);
    }
    return true;
  }
  return false;
}
