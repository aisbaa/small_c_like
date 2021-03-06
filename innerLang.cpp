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

  try {
    while (true)
      fgetNextInnerValue();
  } catch(int cought) {
    if (cought != STREAM_IS_NOT_GOOD_FOR_READING) throw ;
  }
}

InnerLang::~InnerLang() {
  for (this->it = this->LangReservedWords.begin() ; this->it != this->LangReservedWords.end(); this->it++)
    this->LangReservedWords.erase(this->it);
}

int InnerLang::fgetNextInnerValue() {
  string outerValue = this -> stream -> getNextEntity();
  string goesInnerValue = this -> stream -> getNextEntity();

  if (!isDecimalNumber(goesInnerValue.c_str())) throw NOT_UNSIGNED_INT;
    
  int innerValue = atoi(goesInnerValue.c_str());

  this->LangReservedWords.insert(pair<string, int>(outerValue, innerValue));

  return innerValue;
}

bool InnerLang::isCharacter(const string * pretender) {
  if (pretender -> length() != 3) return false;
  if ((*pretender)[0] != '\'') return false;

  return ((*pretender)[pretender -> length() -1] == '\'');
}

bool InnerLang::isString(const string * pretender) {
  if ((*pretender)[0] != '"') return false;
  return ((*pretender)[pretender -> length() -1] == '"');
}

/*
 * PUBLIC
 */
int InnerLang::getInnerLangValue(string outerValue) {
  this->it = this->LangReservedWords.find(outerValue);

  // int idOfReservedWord = this->it->second;
  // int maximumIdOfWords = this->LangReservedWords.size();

  if (this -> it != this -> LangReservedWords.end())
    return this->it->second;

  if (isDecimalNumber(outerValue.c_str()))
    return _INT_VAL_;

  if (isCharacter(&outerValue))
    return _CHAR_VAL_;

  if (isString(&outerValue))
    return _STR_VAL_;

  return _ID_VAL_;
}

string InnerLang::getOuterLangValue(int innerLangValue) {
  switch (innerLangValue) {
  case _INT_VAL_:
    return "intger";
    break;

  case _CHAR_VAL_:
    return "character";
    break;

  case _STR_VAL_:
    return "string";
    break;

  case _ID_VAL_:
    return "_id_";
    break;

  default:
    for (
         innerValueMapInterator it = this -> LangReservedWords.begin();
         it != this -> LangReservedWords.end();
         it++
         )
      if (it -> second == innerLangValue)
        return it -> first;
    break;
  }

  return "";
}
