#ifndef SMALL_C_LIKE_SYNTAX
#define SMALL_C_LIKE_SYNTAX

#include <fstream>
#include <map>

#include "textstream.h"

using namespace std;

typedef map<string,int> syntaxValueMap;
typedef map<string,int>::iterator syntaxValueMapInterator;

class Syntax {

 private:
    
    TextStream * stream;
    ifstream   * file;

    string syntax[100][3];
    
    int index;

    string delimiter;


    void makeSyntax();

    string makeLeftValue();

    bool isNumber(string);

    int convertToInteger(string);

 public:

    Syntax::Syntax(string);

    int getSize();

    string getTerminal(int);
    string getWord(int);
    string getLeftValue(int);
};

#endif
