#ifndef SMALL_C_LIKE_SYNTAX
#define SMALL_C_LIKE_SYNTAX

#include <fstream>
#include <map>

#include "textstream.h"

using namespace std;

typedef map<string,int> syntaxValueMap;
typedef map<string,int>::iterator syntaxValueMapInterator;

/* we need only these */
typedef map<int, int> tokenOverNewState;
typedef map<int, tokenOverNewState> matrix;

const int action_pop = 0;
const int action_push = 1;
const int action_reduction = 2;

class Syntax {

 private:  
    TextStream * stream;
    ifstream   * file;

    int syntax[100][3];
    
    int index;

    string delimiter;


    void makeSyntax();
    void makeWithOneRightValue(string);
    void makeWithTwoRightValues(string);

    string makeLeftValue();

    bool isNumber(string);

    int convertToInteger(string);

 public:
    Syntax(string);

    void printSyntaxValues();

    int getSize();

    int getTerminal(int);
    int getAugment(int);
    int getLeftValue(int);

    /**
     * returns action
     *   reduction
     *   push
     *   pop
     */
    int getNextState(int prev_state, int token, int * new_state);
};

#endif
