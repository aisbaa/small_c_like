#include <iostream>
#include <fstream>
#include <queue>

#include "innerLang.h"

using namespace std;

InnerLang::InnerLang(string fileName) {
  /* if no file exception should be thrown */
  fstream file(fileName.c_str(), ios_base::in);

  while (!file.fail()) {
    this -> LangReservedWords.push(fgetNextInnerValue());
    file.close();
  }
  //file.close(); // this line should realy close file, not above one
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
  return "yey";
}

int InnerLang::fgetNextIntValue() {
  return 99;
}

/*
 * Functionality for user
 */

int InnerLang::getInnerLangValue(string *outerValue) {
  if (this -> LangReservedWords.empty()) {
    /* throw noty exception */
  }

  /* search for value */

  return LangReservedWords.front() -> innervalue;
}
