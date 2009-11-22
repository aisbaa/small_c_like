#include <iostream>
#include <map>
#include <stdlib.h>

#include "ascii_info.h"
#include "innerLang.h"
#include "textstream.h"

using namespace std;

InnerLang::InnerLang(string fileName) {
  this->file   = new ifstream(fileName.c_str(), ios_base::in);
  this->stream = new TextStream(file);

  this -> comment        = &defaultComment;
  this -> commentLineEnd = &defaultCommentLineEnd;

  int maxInnerLangValue = 0;

  while (this->file->good()) {
    maxInnerLangValue = max(
                            fgetNextInnerValue(),
                            maxInnerLangValue
                            );
  }

  this -> innerLangInteger   = ++maxInnerLangValue;
  this -> innerLangCharacter = ++maxInnerLangValue;
  this -> innerLangString    = ++maxInnerLangValue;
  this -> innerLangIndex     = ++maxInnerLangValue;
}

InnerLang::~InnerLang() {
  for (this->it = this->LangReservedWords.begin() ; this->it != this->LangReservedWords.end(); this->it++)
    this->LangReservedWords.erase(this->it);
}

/*
 * PRIVATE
 */
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

int InnerLang::fgetNextInnerValue() {
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

  return innerValue;
}

bool InnerLang::isInteger(const string * pretender) {
  for (unsigned int index = 0; index < pretender -> length(); index++)
    if (!isDecimalDigit((*pretender)[index]))
      return false;
  
  return true;
}

bool InnerLang::isCharacter(const string * pretender) {
  if ((*pretender)[0] != '\'') return false;

  return (
          (*pretender)[pretender -> length() -1]
          ==
          '\''
          );
}

bool InnerLang::isString(const string * pretender) {
  if ((*pretender)[0] != '"') return false;

  return (
          (*pretender)[pretender -> length() -1]
          ==
          '"'
          );
}

/*
 * PUBLIC
 */

int InnerLang::getInnerLangValue(string outerValue) {
  if (this ->LangReservedWords.empty()) {
    /* throw noty exception */
  }

  /* search for value */

  this->it = this->LangReservedWords.find(outerValue);

  int idOfReservedWord = this->it->second;
  int maximumIdOfWords = this->LangReservedWords.size();

  if (idOfReservedWord <= maximumIdOfWords && idOfReservedWord >= 0)
    return this->it->second;

  if (isInteger(&outerValue))
    return this -> innerLangInteger;

  if (isCharacter(&outerValue))
    return this -> innerLangCharacter;

  if (isString(&outerValue))
    return this -> innerLangString;

  return innerLangIndex;
}

int InnerLang::getInnerLangIntegerValue() {
  return this ->  innerLangInteger;
}
int InnerLang::getinnerLangCharacterValue() {
  return this -> innerLangCharacter;
}

int InnerLang::getinnerLangStringValue() {
  return this -> innerLangString;
}

int InnerLang::getinnerLangIndexValue() {
  return this -> innerLangIndex;
}

string *InnerLang::getAllValues() {
    int size = this->LangReservedWords.size();
    int index = 0;
    string * values;

    values = new string[size];
    
    for (this->it = this->LangReservedWords.begin(); this->it != this->LangReservedWords.end(); this->it++) {
	if (this->it->first != "bad stream") {
	    values[index] = this->it->first;
	    index++;
	}
    }

    return values;
}

int InnerLang::getSize() {
    return this->LangReservedWords.size();
}
