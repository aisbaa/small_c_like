#ifndef SMALL_C_LIKE_REWRITER_TOOL
#define SMALL_C_LIKE_REWRITER_TOOL

#include <fstream>
#include <map>

#include "textstream.h"

using namespace std;

typedef map<string,int> syntaxValueMap;
typedef map<string,int>::iterator syntaxValueMapInterator;

const string defaultDelimiter = "::=";

class RewriterTool {

 private:
    
    TextStream * stream;
    ifstream   * file;

    string buffer;
    string outFile;
    string syntax[][3];

    const string * delimiter;

    syntaxValueMap syntaxMap;
    string augmentMap[][2];
    syntaxValueMapInterator it;
    int index;

    void parseAll();

    void valueIsWord(string);

    bool isDelimiter(string);
    bool isCharNumber(char);
    bool isNumber(string);
    bool isWhitespace(char);

    void writeToFile();

    int convertToInteger(string);

 public:

    RewriterTool(string);

};

#endif
