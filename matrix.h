#ifndef SMALL_C_LIKE_MATRIX
#define SMALL_C_LIKE_MATRIX

#include <map>
#include "syntax.h"

using namespace std;

typedef map<int,int> MatrixMap;
typedef map<int,int>::iterator matrixMapIterator;

class Matrix {

 private:
    Syntax * syntax;

    MatrixMap row;
    MatrixMap column;

    int ** matrix;

    matrixMapIterator it;
    
    /*
     * METHODS
     */

    void buildColumns();
    void buildRows();
    void allocateMatrixMemory();
    void fillMatrixValues();

 public:
    Matrix::Matrix(Syntax *);

    void printColumnValues();
    void printRowValues();
    void printMatrix();

    /*
     * GETTERS
     */

    int returnActionNumber(int, int);
};

#endif
