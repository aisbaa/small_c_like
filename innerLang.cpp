#include <iostream>
#include <map>
#include <stdlib.h>

#include "innerLang.h"
#include "textstream.h"
#include "innerLangValues.h"

using namespace std;

InnerLang::InnerLang(string fileName) {
  this->file   = new ifstream(fileName.c_str(), ios_base::in);
  this->stream = new TextStream(file);

  this -> comment        = &defaultComment;
  this -> commentLineEnd = &defaultCommentLineEnd;

  while (this->file->good()) {
	fgetNextInnerValue();
  }
}

InnerLang::~InnerLang() {
  map<string,int>::iterator it;
  for (it = this->LangReservedWords.begin() ; it != this->LangReservedWords.end(); it++)
    this->LangReservedWords.erase(it);
}

bool InnerLang::containsAtBegining(const string * base, const string * needle) {
  string compare =  base -> substr(0, needle -> length());
  return (compare == *needle);
}

bool InnerLang::isCommentOneLine() {
  return containsAtBegining(&(this -> buff), this -> comment);
}


bool InnerLang::isComment() {
  return isCommentOneLine();
}

void InnerLang::skipComment() {
  string skippedComment;

  if (isCommentOneLine())
    skippedComment = this -> stream -> skipToCharacterSequence(this -> commentLineEnd);
}

bool InnerLang::isDigit() {
  if (atoi((this->buff).c_str())) return true;
  return false;
}

void InnerLang::fgetNextInnerValue() {
  do {
    this -> buff = this -> stream -> getNextEntity();
    if (isComment()) skipComment();
  } while (isComment());

  string outerValue;
  int    innerValue;

  do {
	outerValue += this->buff;
    this->buff = this->stream->getNextEntity();
  } while (!isDigit() && this->file->good());

  innerValue = atoi((this->buff).c_str());

  this->LangReservedWords.insert(pair<string, int>(outerValue, innerValue));

  //cout << outerValue << " - " << innerValue << endl;
}

/*
 * Functionality for user
 */

int InnerLang::getInnerLangValue(string outerValue) {
  if (this ->LangReservedWords.empty()) {
    /* throw noty exception */
  }

  /* search for value */
  //return LangReservedWords.front() -> innervalue;

  map<string,int>::iterator it;

  it = this->LangReservedWords.find(outerValue);
  return it->second;
}
