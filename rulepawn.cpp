#include <iostream>
#include <queue>
#include <stdlib.h>

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

  this->currentAnyAlnumPosition  = -1;
  this->currentAnyAlphaPosition  = -1;
  this->currentAnyNumberPosition = -1;

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
        this->anyAlnumPositions.push(i);
	  }
	  else if (this->rule[i] == this->anyAlpha[0]) {
        this->hasAny = true;
        this->hasAnyAlpha = true;
        this->anyAlphaPositions.push(i);
	  }
	  else if (this->rule[i] == this->anyNumber[0]) {
        this->hasAny = true;
        this->hasAnyNumber = true;
        this->anyNumberPositions.push(i);
	  }
  }
  if (!this->anyAlnumPositions.empty())  this->currentAnyAlnumPosition  = this->anyAlnumPositions.front();
  if (!this->anyAlphaPositions.empty())  this->currentAnyAlphaPosition  = this->anyAlphaPositions.front();
  if (!this->anyNumberPositions.empty()) this->currentAnyNumberPosition = this->anyNumberPositions.front();
}

void RulePawn::getNextAlnumPosition() {
  if (!this->anyAlnumPositions.empty()) {
    this->anyAlnumPositions.pop();
    if (!this->anyAlnumPositions.empty())
      this->currentAnyAlnumPosition = this->anyAlnumPositions.front();
  }
}

void RulePawn::getNextAlphaPosition() {
  if (!this->anyAlphaPositions.empty()) {
    this->anyAlphaPositions.pop();
    if (!this->anyAlphaPositions.empty())
      this->currentAnyAlphaPosition = this->anyAlphaPositions.front();
  }
}

void RulePawn::getNextNumberPosition() {
  if (!this->anyNumberPositions.empty()) {
    this->anyNumberPositions.pop();
    if (!this->anyNumberPositions.empty())
      this->currentAnyNumberPosition = this->anyNumberPositions.front();
  }
}

void RulePawn::checkIfPassed() {
  if (this->buff == this->rule)
    this->isPassed = true;
  else
    this->isPassed = false;
}

bool RulePawn::skipAnyAlnum(char value) {
  if (!this->buff[this->current]) this->buff += this->anyAlnum;
  int nextCharacter = this->current + 1;
  if (this->rule[nextCharacter] == value) {
    this->buff += value;
    this->current += 2;
    getNextAlnumPosition();
    return true;
  }
  return true;
}
bool RulePawn::skipAnyAlpha(char value) {
  if (!this->buff[this->current]) this->buff += this->anyAlpha;
  int nextCharacter = this->current + 1;
  if (this->rule[nextCharacter] == value) {
    this->buff += value;
    this->current += 2;
    getNextAlphaPosition();
    return true;
  }
  if (!atoi(&value)) return true;
  this->buff += this->anyAlpha;
  this->buff += value;
  this->current += 1;
  return false;
}

bool RulePawn::skipAnyNumber(char value) {
  if (!this->buff[this->current]) this->buff += this->anyNumber;
  int nextCharacter = this->current + 1;
  if (this->rule[nextCharacter] == value) {
    this->buff += value;
    this->current += 2;
    getNextNumberPosition();
    return true;
  }
  if (atoi(&value)) return true;
  this->buff += this->anyNumber;
  this->buff += value;
  this->current += 1;
  return false;
}

bool RulePawn::isPartOfRuleWithSpec(char value) {
  if (this->current == this->currentAnyAlnumPosition)  return skipAnyAlnum(value);
  if (this->current == this->currentAnyAlphaPosition)  return skipAnyAlpha(value);
  if (this->current == this->currentAnyNumberPosition) return skipAnyNumber(value);
  return isPartOfRuleWithoutSpec(value);
}

bool RulePawn::isPartOfRuleWithoutSpec(char value) {
  this->buff += value;
  if (this->rule[this->current] == value) {
    this->current += 1;
    return true;
  }
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
  checkIfPassed();
  cout << "Rule: " << this->rule << endl;
  cout << "Buff: " << this->buff << endl;
  return this->isPassed;
}

bool RulePawn::pass(char value) {
  return isPartOfRule(value);
}
