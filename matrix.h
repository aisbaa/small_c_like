#ifndef SMALL_C_LIKE_MATRIX
#define SMALL_C_LIKE_MATRIX

#include <map>

#include "innerLang.h"

using namespace std;

const string defaultMarker = "$";

typedef map<string, int> MatrixMap;

class Matrix {

 private:

    InnerLang * lang;

    MatrixMap row;
    MatrixMap column;

    int ** matrix;

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
    Matrix::Matrix(InnerLang *);

    void printColumnValues();

    /*
     * GETTERS
     */

    /* Get matrix value by ROW and COLUMN names */
    int returnActionNumber(string, string);

};

#endif
