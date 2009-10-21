#include <iostream>
#include "rulepawn.h"

using namespace std;

RulePawn::RulePawn(string rule) {
  this->rule     = rule;
  this->current  = 0;
  this->isPassed = false;

  this->hasAny       = false;
  this->hasAnyAlnum  = false;
  this->hasAnyAlpha  = false;
  this->hasAnyNumber = false;

  this->anyAlnum  = defaultAnyAlnum;
  this->anyAlpha  = defaultAnyAlpha;
  this->anyNumber = defaultAnyNumber;

  this->anyAlnumPosition  = -1;
  this->anyAlphaPosition  = -1;
  this->anyNumberPosition = -1;

  hasRuleAnyCharacter();
}

RulePawn::~RulePawn() {}

/*
 * Private methods
 */

void RulePawn::hasRuleAnyCharacter() {
  int loopTo = this->rule.length();
  for (int i = 0; i < loopTo; i++) {
	  if (this->rule[i] == this->anyAlnum[0]) {
        this->hasAny = true;
        this->hasAnyAlnum = true;
        this->anyAlnumPosition = i;
	  }
	  else if (this->rule[i] == this->anyAlpha[0]) {
        this->hasAny = true;
        this->hasAnyAlpha = true;
        this->anyAlphaPosition = i;
	  }
	  else if (this->rule[i] == this->anyNumber[0]) {
        this->hasAny = true;
        this->hasAnyNumber = true;
        this->anyNumberPosition = i;
	  }
  }
}

void RulePawn::checkIfPassed() {
  if (this->buff == this->rule)
    this->isPassed = true;
  else
    this->isPassed = false;
}

bool RulePawn::skipAnyAlnum(char value) {
  int nextRulePosition = this->current + 1;
  if (value == this->rule[nextRulePosition]) {
    this->current += 1;
    this->buff += this->anyAlnum;
    this->buff += value;
  }
  return true;
}
bool RulePawn::skipAnyAlpha(char value) {
  if (!atoi(&value)) {
    int nextRulePosition = this->current + 1;
    if (value == this->rule[nextRulePosition]) {
      this->current += 1;
      this->buff += this->anyAlpha;
      this->buff += value;
    }
    return true;
  }
  return false;
}
bool RulePawn::skipAnyNumber(char value) {
  int nextRulePosition = this->current + 1;
  if (value == this->rule[nextRulePosition]) {
    this->current += 1;
    this->buff += this->anyNumber;
    this->buff += value;
    return true;
  }
  if (atoi(&value)) return true;
  this->buff += value;
  return false;
}

bool RulePawn::isPartOfRuleWithSpec(char value) {
  if (this->current == this->anyAlnumPosition)  return skipAnyAlnum(value);
  else if (this->current == this->anyAlphaPosition)  return skipAnyAlpha(value);
  else if (this->current == this->anyNumberPosition) return skipAnyNumber(value);
  else return isPartOfRuleWithoutSpec(value);
}

bool RulePawn::isPartOfRuleWithoutSpec(char value) {
  this->current += 1;
  this->buff += value;
  checkIfPassed();
  if (this->rule[this->current] == value) return true;
  return false;
}

bool RulePawn::isPartOfRule(char value) {
  if (this->hasAny) return isPartOfRuleWithSpec(value);
  else return isPartOfRuleWithoutSpec(value);
}

/*
 * Public methods
 */

void RulePawn::reset() {
  this->current  = 0;
  this->isPassed = false;
}

bool RulePawn::passed() {
  cout << "Rule: " << this->rule << endl;
  cout << "Buff: " << this->buff << endl;
  return this->isPassed;
}

bool RulePawn::pass(char value) {
  return isPartOfRule(value);
}
