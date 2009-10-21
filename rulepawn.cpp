#include <iostream>
#include "rulepawn.h"

using namespace std;

RulePawn::RulePawn(string rule) {
  this->rule     = rule;
  this->current  = 0;
  this->isPassed = false;
  this->hasAnyChar = false;

  hasRuleAnyCharacter();
}

RulePawn::~RulePawn() {}

/*
 * Private methods
 */

void RulePawn::hasRuleAnyCharacter() {
  string spec = "@";
  int loopTo = this->rule.length();
  for (int i = 0; i < loopTo; i++) {
	  if (this->rule[i] == spec[0]) {
        this->hasAnyChar = true;
        this->anyCharacterPosition = i;
	  }
  }
}

void RulePawn::checkIfPassed() {
  if (this->buff == this->rule)
    this->isPassed = true;
  else
    this->isPassed = false;
}

bool RulePawn::isPartOfRuleWithSpec(char value) {
  if (this->current == this->anyCharacterPosition) {
    int nextRulePosition = this->current + 1;
    if (value == this->rule[nextRulePosition]) {
      this->current +=1;
      this->buff += "@";
      this->buff += value;
      checkIfPassed();
    }
    return true;
  }
  else {
    isPartOfRuleWithoutSpec(value);
  }
}

bool RulePawn::isPartOfRuleWithoutSpec(char value) {
  this->current += 1;
  this->buff += value;
  checkIfPassed();
  if (this->rule[this->current] == value) return true;
  return false;
}

bool RulePawn::isPartOfRule(char value) {
  if (this->hasAnyChar) return isPartOfRuleWithSpec(value);
  return isPartOfRuleWithoutSpec(value);
}

/*
 * Public methods
 */

void RulePawn::reset() {
  this->buff     = "";
  this->current  = -1;
  this->isPassed = false;
  this->hasAnyChar = false;
}

bool RulePawn::passed() {
  cout << "Rule: " << this->rule << endl;
  cout << "Buff: " << this->buff << endl;
  return this->isPassed;
}

bool RulePawn::pass(char value) {
  return isPartOfRule(value);
}
