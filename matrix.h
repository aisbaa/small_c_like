#ifndef SMALL_C_LIKE_MATRIX
#define SMALL_C_LIKE_MATRIX

#include <map>
#include <vector>

#include "innerLang.h"
#include "syntax.h"

using namespace std;

const string defaultMarker = "$";

typedef map<string, int> MatrixMap;

class Matrix {

 private:

    InnerLang * lang;

    Syntax * syntax;

    MatrixMap row;
    MatrixMap column;

    string ** matrix;

    map<string, int>::iterator it;

    const string * marker;
    
    /*
     * METHODS
     */

    /* Building matrix columns*/
    void buildColumns();

    /* Building matrix rows */
    void buildRows();

    /* Allocating matrix memory */
    void allocateMatrixMemory();

    /* Filling values */
    void fillMatrixValues();

 public:
    Matrix::Matrix(InnerLang *, Syntax *);

    void printColumnValues();
    void printRowValues();

    /*
     * GETTERS
     */

    /* Get matrix value by ROW and COLUMN names */
    int returnActionNumber(string, string);

    string returnActionValue(string, string);

};

#endif
