#ifndef SMALL_C_LIKE_SYNTAX
#define SMALL_C_LIKE_SYNTAX

#include <fstream>
#include <map>
#include <vector>

#include "textstream.h"

using namespace std;

typedef map<string,int> syntaxValueMap;
typedef map<string,int>::iterator syntaxValueMapInterator;

/* we need only these */
//typedef map<int, int> tokenOverNewState;
//typedef map<int, tokenOverNewState> matrix;

typedef struct {
    int newState;
    int state;
    int term;
    char action;
} MatrixValues;

typedef vector<MatrixValues> Matrix;
typedef vector<MatrixValues>::iterator MatrixIterator;

const int action_pop = 0;
const int action_push = 1;
const int action_reduction = 2;

class Syntax {

 private:  
    TextStream * stream;
    ifstream   * file;

    Matrix matrix;
    MatrixIterator it;

    void parseFile();
    void fillMatrix();

    int makeNumber();
    char makeAction();
    int convertToInteger(string);

    bool isNumber(string);

    int getActionNumber(char);

    MatrixValues findMatrix(int, int);

 public:
    Syntax(string);

    void printMatrix();

    int getNewState(int, int);
    /**
     * returns action
     *   reduction
     *   push
     *   pop
     */
    int getNextState(int prev_state, int token, int * new_state);
};

#endif
