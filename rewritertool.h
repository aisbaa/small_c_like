#ifndef SMALL_C_LIKE_REWRITER_TOOL
#define SMALL_C_LIKE_REWRITER_TOOL

#include <fstream>
#include <map>

#include "textstream.h"

using namespace std;

typedef map<string,int> syntaxValueMap;
typedef map<string,int>::iterator syntaxValueMapInterator;

class RewriterTool {
 private:
  ifstream * file;

  int index;

  syntaxValueMap syntaxMap;
  syntaxValueMapInterator it;

  /*
  vector<string> tokens;
  string str("Split me up! Word1 Word2 Word3.");
  */

 private:
  void parseAll();

  int convertToInteger(string);

 public:
  RewriterTool(string);

};

#endif
