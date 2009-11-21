#ifndef SMALL_C_LIKE_SYNTAX_MATRIX
#define SMALL_C_LIKE_SYNTAX_MATRIX

#include <fstream>

#include "textstream.h"

using namespace std;

const string defaultDelimeter = "::=";
//const string defaultEndOfRule = "#";

class SyntaxMatrix {

 private:
    ifstream   * file;
    TextStream * stream;

    string *  leftSides;
    string ** rightSides;

    const string * delimeter;
    const string * endOfRule;

    string buildRule();

    string buildLeft();

 public:
    SyntaxMatrix::SyntaxMatrix(string);

    void parseAll();

    /*
     * GETTERS
     */

    int getActionNumber(string);

};

#endif
