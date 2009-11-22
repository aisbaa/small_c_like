#ifndef SMALL_C_LIKE_SYNTAX_MATRIX
#define SMALL_C_LIKE_SYNTAX_MATRIX

#include <fstream>
#include <map>

#include "textstream.h"
#include "innerLang.h"

using namespace std;

const string defaultDelimeter = "::=";
const string defaultEndOfRule = "#";

typedef map<string, int> customMap;

class SyntaxMatrix {

 private:
    ifstream   * file;
    TextStream * stream;
    InnerLang  * lang;

    int ** matrix;

    customMap TerminalMap;
    customMap RowMap;

    map<string, int>::iterator it;

    const string * delimeter;
    const string * endOfRule;

    void parseAll();
    void buildMatrix();
    
    /* These methods parse left and right sides of grammar */
    /* TODO:
     *   - rewrite more intelligent parser
     */
    string buildRule();
    string buildLeft();

    /* Tells if we have this term in our matrix */
    bool isDefinedTerminal(string);
    /* Tells if it is inner lang value */
    bool isInnerLangValue(string);

    /* Add terminal to our matrix */
    void addTerminal(string);

    void printTerminals();
    void printRows();
    void printMatrix();

 public:
    SyntaxMatrix::SyntaxMatrix(string, InnerLang *);

    /*
     * GETTERS
     */

    int getNumberByRow(string);

    int getNumberByColumn(string);

    int ** getMatrix();

};

#endif
