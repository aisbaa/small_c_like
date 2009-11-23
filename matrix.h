#ifndef SMALL_C_LIKE_MATRIX
#define SMALL_C_LIKE_MATRIX

#include <map>
#include <vector>

#include "innerLang.h"
#include "syntax.h"

using namespace std;

typedef map<int,int> MatrixMap;
typedef map<int,int>::iterator matrixMapIterator;

class Matrix {

 private:
    InnerLang * lang;
    Syntax    * syntax;

    MatrixMap row;
    MatrixMap column;

    int ** matrix;

    matrixMapIterator it;
    
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
    void printMatrix();

    /*
     * GETTERS
     */

    int returnActionNumber(int, int);
};

#endif
