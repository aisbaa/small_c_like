#include <iostream>
#include <map>
#include <vector>

#include "matrix.h"
#include "syntax.h"

using namespace std;

Matrix::Matrix(Syntax * syntax) {
    this->syntax = syntax;
}
