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

  /* if no file exception should be thrown */
  //fstream file(fileName.c_str(), ios_base::in);

  //while (!file.fail()) {
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

innerValueEntry * InnerLang::fgetNextInnerValue() {
  innerValueEntry * value = new innerValueEntry;
  value -> outervalue = fgetNextStringValue();
  value -> innervalue = fgetNextIntValue();

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
