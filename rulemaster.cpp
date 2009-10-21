#include <vector>
#include <iostream>
#include <fstream>

#include "rulemaster.h"

using namespace std;

RuleMaster::RuleMaster(string ruleFileName) {
  ifstream   file(ruleFileName.c_str(), ifstream::in);

  while (file.good()) {
    string strRule;
    getline(file, strRule);
    
    if (!strRule.empty())
      this -> ruleflock.push_back(new RulePawn(strRule));
  }

  file.close();
}

RuleMaster::~RuleMaster() {
  while (!this -> ruleflock.empty()) {
    delete this -> ruleflock.back();
    this -> ruleflock.pop_back();
  }
}

bool RuleMaster::match(char testChar) {
  vector<RulePawn *>::iterator rule = this -> ruleflock.begin();
  bool allfailed = true;

  while (rule != this -> ruleflock.end()) {
    /*
     * Passing testChar to each rule and checking if
     * atleast one rule passes
     */

    if ((*rule) -> pass(testChar) && allfailed)
      allfailed = false;

    rule++;
  }

  return !allfailed;
}

bool RuleMaster::haveComplete() {
  vector<RulePawn *>::iterator rule = this -> ruleflock.begin();

  while (rule != this -> ruleflock.end()) {
    if ((*rule) -> passed())
      return true;
    rule++;
  }

  return false;
}

void RuleMaster::reset() {
  for (
       vector<RulePawn *>::iterator rule = this -> ruleflock.begin();
       rule != this -> ruleflock.end();
       rule++
       )
    (*rule) -> reset();
}
