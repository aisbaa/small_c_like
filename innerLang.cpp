#include <iostream>
#include <fstream>
#include <istream>
#include <queue>

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
    this -> LangReservedWords.push(fgetNextInnerValue());
  }

}

InnerLang::~InnerLang() {
  while (!this -> LangReservedWords.empty()) {
    delete (innerValueEntry *) (this -> LangReservedWords.front());
    this -> LangReservedWords.pop();
  }
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

innerValueEntry * InnerLang::fgetNextInnerValue() {
  do {
    this -> buff = this -> stream -> getNextEntity();
    if (isComment()) skipComment();
  } while (isComment());

  innerValueEntry * value = new innerValueEntry;
  value -> outervalue = this -> buff;
  value -> innervalue = fgetNextIntValue();

  //cout << value->outervalue << " - " << value->innervalue << endl;

  return value;
}

string InnerLang::fgetNextStringValue() {
  return this->stream->getNextEntity();
}

int InnerLang::fgetNextIntValue() {
  return atoi(this->stream->getNextEntity().c_str());
}

int InnerLang::searchInnerLangValue(string outerValue) {
	queue<innerValueEntry *> tempLangReservedWords = this->LangReservedWords;
	while (!tempLangReservedWords.empty()) {
		if (tempLangReservedWords.front()->outervalue == outerValue) {
			return tempLangReservedWords.front()->innervalue;
		}
		tempLangReservedWords.pop();
	}
	return -1;
}

/*
 * Functionality for user
 */

int InnerLang::getInnerLangValue(string outerValue) {
  if (this -> LangReservedWords.empty()) {
    /* throw noty exception */
  }

  /* search for value */
  //return LangReservedWords.front() -> innervalue;
  return searchInnerLangValue(outerValue);
}
